//
// Created by aucker on 10/7/2023.
//
#ifndef CLOX_VM_H
#define CLOX_VM_H


//#include "chunk.h"
#include "object.h"
#include "table.h"
#include "value.h"

//#define STACK_MAX 256
#define FRAMES_MAX 64
#define STACK_MAX (FRAMES_MAX * UINT8_COUNT)

typedef struct {
//    ObjFunction* function;
    ObjClosure* closure;
    uint8_t* ip;
    Value* slots;
} CallFrame;


/*
 * If we were trying to squeeze every ounce of speed out of our bytecode interpreter,
 * we would store `in` in a local variable. It gets modified so often during execution
 * that we want the C compiler to keep it in a register.
 */
typedef struct {
//    Chunk* chunk;
//    uint8_t* ip;
    CallFrame frames[FRAMES_MAX];
    int frameCount;

    Value stack[STACK_MAX];
    Value* stackTop;
    Table globals;
    Table strings;
    ObjUpvalue* openUpvalues;
    Obj* objects;
} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

// The 'object' module is directly using the global `vm` variable
// from the "vm" module, so we need to expose that externally
extern VM vm;

void initVM();
void freeVM();
//InterpretResult interpret(Chunk* chunk);
InterpretResult interpret(const char* source);
void push(Value value);
Value pop();

#endif//CLOX_VM_H
