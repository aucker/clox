//
// Created by aucker on 10/7/2023.
//

#include "vm.h"
#include "common.h"
#include "compiler.h"
#include "debug.h"
#include "memory.h"
#include "object.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

VM vm;

static void resetStack() {
    // free the stack, now empty
    vm.stackTop = vm.stack;
    vm.frameCount = 0;
}

static void runtimeError(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fputs("\n", stderr);

//    size_t instruction = vm.ip - vm.chunk->code - 1;
//    int line = vm.chunk->lines[instruction];
    CallFrame* frame = &vm.frames[vm.frameCount - 1];
    size_t instruction = frame->ip - frame->function->chunk.code - 1;
    int line = frame->function->chunk.lines[instruction];
    fprintf(stderr, "[line %d] in script\n", line);
    resetStack();
}

void initVM() {
    resetStack();
    vm.objects = NULL;

    // we need to initialize the hash table to a valid state
    initTable(&vm.globals);
    // when we spin up a new VM, the string table is empty
    initTable(&vm.strings);
}

void freeVM() {
    freeTable(&vm.globals);
    // when we shut down the VM, we clean up any resources used by the table.
    freeTable(&vm.strings);
    freeObjects();
}

/*
 * This is how push stack works
 * in a pure pointer view
 */
void push(Value value) {
    *vm.stackTop = value;
    vm.stackTop++;
}

// pointer view of pop stack
Value pop() {
    vm.stackTop--;
    return *vm.stackTop;
}

static Value peek(int distance) {
    return vm.stackTop[-1 - distance];
}

/*
 * This is the helper function in callValue()
 * because Lox is dynamically typed, so we have to report
 * the type error ourselves
 */
static bool call(ObjFunction* function, int argCount) {
    if (argCount != function->arity) {  // we check the arity here
        runtimeError("Expected %d arguments but got $d.",
                     function->arity, argCount);
        return false;
    }

    // because CallFrame has a fixed size, we need to ensure a deep call
    // chain doesn't overflow it.
    if (vm.frameCount == FRAMES_MAX) {  // we check CallFrame array here
        runtimeError("Stack overflows.");
        return false;
    }

    CallFrame* frame = &vm.frames[vm.frameCount++];
    frame->function = function;
    frame->ip = function->chunk.code;
    frame->slots = vm.stackTop - argCount - 1;
    return true;
}

// this is the helper function in run() func
static bool callValue(Value callee, int argCount) {
    if (IS_OBJ(callee)) {
        switch (OBJ_TYPE(callee)) {
            case OBJ_FUNCTION:
                return call(AS_FUNCTION(callee), argCount);
            default:
                break; // Non-callable object type.
        }
    }
    runtimeError("Can only call functions and classes");
    return false;
}

static bool isFalsey(Value value) {
    return IS_NIL(value) || (IS_BOOL(value) && !AS_BOOL(value));
}

static void concatenate() {
    ObjString *b = AS_STRING(pop());
    ObjString *a = AS_STRING(pop());

    int length = a->length + b->length;
    char *chars = ALLOCATE(char, length + 1);
    memcpy(chars, a->chars, a->length);
    memcpy(chars + a->length, b->chars, b->length);
    chars[length] = '\0';

    ObjString *result = takeString(chars, length);
    push(OBJ_VAL(result));
}

static InterpretResult run() {
    CallFrame *frame = &vm.frames[vm.frameCount - 1];

#define READ_BYTE() (*frame->ip++)

#define READ_SHORT() \
    (frame->ip += 2, \
     (uint16_t) ((frame->ip[-2] << 8) | frame->ip[-1]))

#define READ_CONSTANT() \
    (frame->function->chunk.constants.values[READ_BYTE()])
//#define READ_BYTE() (*vm.ip++)
//#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
//#define READ_SHORT() \
    (vm.ip += 2, (uint16_t)((vm.ip[-2] << 8) | vm.ip[-1]))
#define READ_STRING() AS_STRING(READ_CONSTANT())
    /*
     * Did you even know you can pass an *operator* as an argument to a macro?
     * The preprocessor doesn't care that operators aren't first class in C.
     * It's just text tokens for the preprocessor.
     */
//#define BINARY_OP(op)     \
//    do {                  \
//        double b = pop(); \
//        double a = pop(); \
//        push(a op b);     \
//    } while (false)
/*
 * Note the *order* of two pops matters.
 * When the operands themselves are calculated, the left is evaluated first,
 * then the right. That means the left operand gets pushed before the right
 * operand. So the right operand will be on top of the stack.
 */
#define BINARY_OP(valueType, op)                          \
    do {                                                  \
        if (!IS_NUMBER(peek(0)) || !IS_NUMBER(peek(1))) { \
            runtimeError("Operands must be numbers.");    \
            return INTERPRET_RUNTIME_ERROR;               \
        }                                                 \
        double b = AS_NUMBER(pop());                      \
        double a = AS_NUMBER(pop());                      \
        push(valueType(a op b));                          \
    } while (false)

    for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
        printf("        ");
        for (Value *slot = vm.stack; slot < vm.stackTop; slot++) {
            printf("[ ");
            printValue(*slot);
            printf(" ]");
        }
        printf("\n");
//        disassembleInstruction(vm.chunk,
//                               (int) (vm.ip - vm.chunk->code));
        disassembleInstruction(&frame->function->chunk,
                               (int)(frame->ip - frame->function->chunk.code));
#endif
        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                //                    printValue(constant);
                //                    printf("\n");
                push(constant);
                break;
            }
            case OP_NIL:
                push(NIL_VAL);
                break;
            case OP_TRUE:
                push(BOOL_VAL(true));
                break;
            case OP_FALSE:
                push(BOOL_VAL(false));
                break;
            case OP_POP:
                pop();
                break;
            case OP_GET_LOCAL: {
                uint8_t slot = READ_BYTE();
//                push(vm.stack[slot]);
                push(frame->slots[slot]);
                break;
            }
            case OP_SET_LOCAL: {
                uint8_t slot = READ_BYTE();
//                vm.stack[slot] = peek(0);
                frame->slots[slot] = peek(0);
                break;
            }
            case OP_GET_GLOBAL: {
                ObjString *name = READ_STRING();
                Value value;
                if (!tableGet(&vm.globals, name, &value)) {
                    runtimeError("Undefined variable '%s'.", name->chars);
                    return INTERPRET_RUNTIME_ERROR;
                }
                push(value);
                break;
            }
            case OP_DEFINE_GLOBAL: {
                ObjString *name = READ_STRING();
                tableSet(&vm.globals, name, peek(0));
                pop();
                break;
            }
            case OP_SET_GLOBAL: {
                ObjString *name = READ_STRING();
                if (tableSet(&vm.globals, name, peek(0))) {
                    tableDelete(&vm.globals, name);
                    runtimeError("Undefined variable '%s'.", name->chars);
                    return INTERPRET_RUNTIME_ERROR;
                }
                break;
            }
            case OP_EQUAL: {
                Value b = pop();
                Value a = pop();
                push(BOOL_VAL(valuesEqual(a, b)));
                break;
            }
            case OP_GREATER:
                BINARY_OP(BOOL_VAL, >);
                break;
            case OP_LESS:
                BINARY_OP(BOOL_VAL, <);
                break;
                //            case OP_ADD:
                //                BINARY_OP(+);
                //                BINARY_OP(NUMBER_VAL, +);
                //                break;
            case OP_ADD: {
                if (IS_STRING(peek(0)) && IS_STRING(peek(1))) {
                    concatenate();
                } else if (IS_NUMBER(peek(0)) && IS_NUMBER(peek(1))) {
                    double b = AS_NUMBER(pop());
                    double a = AS_NUMBER(pop());
                    push(NUMBER_VAL(a + b));
                } else {
                    runtimeError(
                            "Operands must be two numbers or two strings.");
                    return INTERPRET_RUNTIME_ERROR;
                }
                break;
            }
            case OP_SUBTRACT:
                //                BINARY_OP(-);
                BINARY_OP(NUMBER_VAL, -);
                break;
            case OP_MULTIPLY:
                //                BINARY_OP(*);
                BINARY_OP(NUMBER_VAL, *);
                break;
            case OP_DIVIDE:
                //                BINARY_OP(/);
                BINARY_OP(NUMBER_VAL, /);
                break;
                //                case OP_NEGATE:   push(-pop()); break;
            case OP_NOT:
                push(BOOL_VAL(isFalsey(pop())));
                break;
            case OP_NEGATE:
                if (!IS_NUMBER(peek(0))) {
                    runtimeError("Operand must be a number.");
                    return INTERPRET_RUNTIME_ERROR;
                }
                push(NUMBER_VAL(-AS_NUMBER(pop())));
                break;
            case OP_PRINT:
                /*
                 * When the interpreter reaches this instruction, it has already executed
                 * the code for the expression, leaving the result value on top of the
                 * stack. Now we simply pop and print it.
                 */
                printValue(pop());
                printf("\n");
                break;
            case OP_JUMP: {
                uint16_t offset = READ_SHORT();
//                vm.ip += offset;
                frame->ip += offset;
                break;
            }
            case OP_JUMP_IF_FALSE: {
                uint16_t offset = READ_SHORT();
//                if (isFalsey(peek(0))) vm.ip += offset;
                if (isFalsey(peek(0))) frame->ip += offset;
                break;
            }
            case OP_LOOP: {
                uint16_t offset = READ_SHORT();
//                vm.ip -= offset;
                frame->ip -= offset;
                break;
            }
            case OP_CALL: {
                int argCount = READ_BYTE();
                if (!callValue(peek(argCount), argCount)) {
                    return INTERPRET_RUNTIME_ERROR;
                }
                /*
                 * If callValue() is successful, there will be a new frame on the
                 * CallFrame stack for the called function. The run() func has its
                 * own cached pointer to the current frame. we need to update it.
                 */
                frame = &vm.frames[vm.frameCount - 1];
                break;
            }
            case OP_RETURN: {
                //                printValue(pop());
                //                printf("\n");
                // Exit interpreter
                return INTERPRET_OK;
            }
        }
    }
#undef READ_BYTE
#undef READ_SHORT
#undef READ_CONSTANT
#undef READ_STRING
#undef BINARY_OP
    /*
         * Undefining these macros explicitly might seem needlessly fastidious, but C
         * tends to punish sloppy users, and the C preprocessor doubly so.
         */
}

//InterpretResult interpret(Chunk* chunk) {
InterpretResult interpret(const char *source) {
    //    vm.chunk = chunk;
    //    vm.ip = vm.chunk->code;
    //    return run();
    //        compile(source);
    //        return INTERPRET_OK;
//    Chunk chunk;
//    initChunk(&chunk);
//
//    if (!compile(source, &chunk)) {
//        freeChunk(&chunk);
//        return INTERPRET_COMPILE_ERROR;
//    }
//
//    vm.chunk = &chunk;
//    vm.ip = vm.chunk->code;
    ObjFunction* function = compile(source);
    if (function == NULL) return INTERPRET_COMPILE_ERROR;

    push(OBJ_VAL(function));

    call(function, 0);
//    CallFrame* frame = &vm.frames[vm.frameCount++];
//    frame->function = function;
//    frame->ip = function->chunk.code;
//    frame->slots = vm.stack;

//    InterpretResult result = run();
//
//    freeChunk(&chunk);
//    return result;
    return run();
}