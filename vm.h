//
// Created by aucker on 10/7/2023.
//

#include "chunk.h"
#include "value.h"

#define STACK_MAX 256

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
    Value stack[STACK_MAX];
    Value* stackTop;
} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

void initVM();
void freeVM();
//InterpretResult interpret(Chunk* chunk);
InterpretResult interpret(const char* source);
void push(Value value);
Value pop();

#endif//CLOX_VM_H
