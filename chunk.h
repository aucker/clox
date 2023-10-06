//
// Created by aucker on 10/7/2023.
//

#ifndef CLOX_CHUNK_H
#define CLOX_CHUNK_H

#include "common.h"

typedef enum {
    OP_RETURN,
} OpCode;

/*
 * Dynamic Array:
 * Cache-friendly, dense storage
 * Constant-time indexed element lookup
 * Constant-time appending to the end of the array
 */
typedef struct {
    int count;
    int capacity;
    uint8_t* code;
} Chunk;

void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte);

#endif//CLOX_CHUNK_H
