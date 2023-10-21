//
// Created by Aucker An on 2023/10/14.
//

#ifndef CLOX_COMPILER_H
#define CLOX_COMPILER_H

#include "object.h"
#include "vm.h"

//void compile(const char* source);
//bool compile(const char* source, Chunk* chunk);
ObjFunction* compile(const char* source);

#endif//CLOX_COMPILER_H
