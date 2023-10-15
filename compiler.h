//
// Created by Aucker An on 2023/10/14.
//

#ifndef CLOX_COMPILER_H
#define CLOX_COMPILER_H

#include "vm.h"

//void compile(const char* source);
bool compile(const char* source, Chunk* chunk);

#endif//CLOX_COMPILER_H
