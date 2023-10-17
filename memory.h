//
// Created by aucker on 10/7/2023.
//

#ifndef CLOX_MEMORY_H
#define CLOX_MEMORY_H

#include "common.h"

#define ALLOCATE(type, count) \
    (type*) reallocate(NULL, 0, sizeof(type) * (count))
/*
 * The right way to pick a value for this is to profile against
 * real-world usage and see which constant makes the best performance
 * trade-off between extra grows versus wasted space.
 */
#define GROW_CAPACITY(capacity) \
    ((capacity) < 8 ? 8 : (capacity) * 2)

#define GROW_ARRAY(type, pointer, oldCount, newCount) \
    (type*)reallocate(pointer, sizeof(type) * (oldCount), \
        sizeof(type) * (newCount))

#define FREE_ARRAY(type, pointer, oldCount) \
    reallocate(pointer, sizeof(type) * (oldCount), 0)

void* reallocate(void* pointer, size_t oldSize, size_t newSize);

#endif//CLOX_MEMORY_H
