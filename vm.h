//
// Created by aucker on 10/7/2023.
//

#include "chunk.h"

#ifndef CLOX_VM_H
#define CLOX_VM_H

/*
 * If we were trying to squeeze every ounce of speed out of our bytecode interpreter,
 * we would store `in` in a local variable. It gets modified so often during execution
 * that we want the C compiler to keep it in a register.
 */
typedef struct {
    Chunk* chunk;
    uint8_t* ip;
} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

void initVM();
void freeVM();
InterpretResult interpret(Chunk* chunk);

#endif//CLOX_VM_H
