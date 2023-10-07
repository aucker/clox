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
        for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
            disassembleInstruction(vm.chunk,
                                   (int)(vm.ip - vm.chunk->code));
#endif
            uint8_t instruction;
            switch (instruction = READ_BYTE()) {
                case OP_CONSTANT: {
                    Value constant = READ_CONSTANT();
                    printValue(constant);
                    printf("\n");
                    break;
                }
                case OP_RETURN: {
                    return INTERPRET_OK;
                }
            }
        }
#undef READ_BYTE
#undef READ_CONSTANT
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