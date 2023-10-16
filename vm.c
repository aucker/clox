//
// Created by aucker on 10/7/2023.
//

#include "vm.h"
#include "common.h"
#include "compiler.h"
#include "debug.h"
#include <stdarg.h>
#include <stdio.h>

VM vm;

static void resetStack() {
    // free the stack, now empty
    vm.stackTop = vm.stack;
}

static void runtimeError(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fputs("\n", stderr);

    size_t instruction = vm.ip - vm.chunk->code - 1;
    int line = vm.chunk->lines[instruction];
    fprintf(stderr, "[line %d] in script\n", line);
    resetStack();
}

void initVM() {
    resetStack();
}

void freeVM() {
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

static InterpretResult run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
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
        disassembleInstruction(vm.chunk,
                               (int) (vm.ip - vm.chunk->code));
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
            case OP_ADD:
//                BINARY_OP(+);
                BINARY_OP(NUMBER_VAL, +);
                break;
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
            case OP_NEGATE:
                if (!IS_NUMBER(peek(0))) {
                    runtimeError("Operand must be a number.");
                    return INTERPRET_RUNTIME_ERROR;
                }
                push(NUMBER_VAL(-AS_NUMBER(pop())));
                break;
            case OP_RETURN: {
                printValue(pop());
                printf("\n");
                return INTERPRET_OK;
            }
        }
    }
#undef READ_BYTE
#undef READ_CONSTANT
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
    Chunk chunk;
    initChunk(&chunk);

    if (!compile(source, &chunk)) {
        freeChunk(&chunk);
        return INTERPRET_COMPILE_ERROR;
    }

    vm.chunk = &chunk;
    vm.ip = vm.chunk->code;

    InterpretResult result = run();

    freeChunk(&chunk);
    return result;
}