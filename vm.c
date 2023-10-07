//
// Created by aucker on 10/7/2023.
//

#include "vm.h"
#include "common.h"
#include "debug.h"
#include <stdio.h>

VM vm;

static void resetStack() {
    // free the stack, now empty
    vm.stackTop = vm.stack;
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

static InterpretResult run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
    /*
     * Did you even know you can pass an *operator* as an argument to a macro?
     * The preprocessor doesn't care that operators aren't first class in C.
     * It's just text tokens for the preprocessor.
     */
#define BINARY_OP(op)     \
    do {                  \
        double b = pop(); \
        double a = pop(); \
        push(a op b);     \
    } while (false)
/*
 * Note the *order* of two pops matters.
 * When the operands themselves are calculated, the left is evaluated first,
 * then the right. That means the left operand gets pushed before the right
 * operand. So the right operand will be on top of the stack.
 */

    for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
            printf("        ");
            for (Value* slot = vm.stack; slot < vm.stackTop; slot++) {
                printf("[ ");
                printValue(*slot);
                printf(" ]");
            }
            printf("\n");
            disassembleInstruction(vm.chunk,
                                   (int)(vm.ip - vm.chunk->code));
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
                case OP_ADD:      BINARY_OP(+); break;
                case OP_SUBTRACT: BINARY_OP(-); break;
                case OP_MULTIPLY: BINARY_OP(*); break;
                case OP_DIVIDE:   BINARY_OP(/); break;
                case OP_NEGATE:   push(-pop()); break;
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

InterpretResult interpret(Chunk* chunk) {
    vm.chunk = chunk;
    vm.ip = vm.chunk->code;
    return run();
}