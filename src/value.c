//
// Created by aucker on 10/7/2023.
//
#include <stdio.h>
#include <string.h>

#include "object.h"
#include "memory.h"
#include "value.h"

void initValueArray(ValueArray* array) {
    array->count = 0;
    array->capacity = 0;
    array->values = NULL;
}

void writeValueArray(ValueArray* array, Value value) {
    if (array->capacity < array->count + 1) {
        int oldCapacity = array->capacity;
        array->capacity = GROW_CAPACITY(oldCapacity);
        array->values = GROW_ARRAY(Value, array->values,
                                   oldCapacity, array->capacity);
    }

    array->values[array->count] = value;
    array->count++;
}

void freeValueArray(ValueArray* array) {
    FREE_ARRAY(Value, array->values, array->capacity);
    initValueArray(array);
}

void printValue(Value value) {
//    printf("%g", value);
//    printf("%g", AS_NUMBER(value));
    switch (value.type) {
        case VAL_BOOL:
            printf(AS_BOOL(value) ? "true" : "false");
            break;
        case VAL_NIL:
            printf("nil"); break;
        case VAL_NUMBER: printf("%g", AS_NUMBER(value)); break;
        case VAL_OBJ: printObject(value); break;
    }
}

bool valuesEqual(Value a, Value b) {
    if (a.type != b.type) return false;
    switch (a.type) {
        case VAL_BOOL:    return AS_BOOL(a) == AS_BOOL(b);
        case VAL_NIL:     return true;
        case VAL_NUMBER:  return AS_NUMBER(a) == AS_NUMBER(b);
//        case VAL_OBJ: {
//            ObjString* aString = AS_STRING(a);
//            ObjString* bString = AS_STRING(b);
//            return aString->length == bString->length &&
//                memcmp(aString->chars, bString->chars,
//                       aString->length) == 0;
//        }
        // we don't need to compare string character-by-character
        /*
         * we've added a little overhead when creating strings to intern them.
         * but in return at runtime, the equality operator on strings is much faster.
         * When that, we have a full-featured hash table ready for us to use for
         * tracking variables, instances, or any other k/v pairs that might show up.
         */
        case VAL_OBJ:     return AS_OBJ(a) == AS_OBJ(b);
        default:          return false;  // unreachable.
    }
}