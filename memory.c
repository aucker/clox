//
// Created by aucker on 10/7/2023.
//
#include <stdlib.h>

#include "memory.h"
#include "vm.h"

/**
 * There're four actions for reallocate, all we care is oldSize and newSize:
 * o->0 & n->non-zero: Allocate new block
 * o->non-zero & n->0: Free allocation
 * o->non-zero & n->smaller than o: Shrink existing allocation
 * o->non-zero & n->larger than o: Grow existing allocation
 * @param pointer
 * @param oldSize
 * @param newSize
 * @return
 */
void* reallocate(void* pointer, size_t oldSize, size_t newSize) {
    if (newSize == 0) {
        free(pointer);
        return NULL;
    }

    // when newSize if zero, we handle deallocation case ourselves by calling `free()`.
    // Otherwise, we rely on C standard library's `realloc()` function.
    void* result = realloc(pointer, newSize);
    if (result == NULL) exit(1);  // allocation fail w/o enough memory
    return result;
}

static void freeObject(Obj* object) {
    switch (object->type) {
        case OBJ_CLOSURE: {
            ObjClosure* closure = (ObjClosure*)object;
            FREE_ARRAY(ObjUpvalue*, closure->upvalues,
                       closure->upvalueCount);

            FREE(ObjClosure, object);
            break;
        }
        case OBJ_FUNCTION: {
            ObjFunction* function = (ObjFunction*)object;
            freeChunk(&function->chunk);
            FREE(ObjFunction, object);
            break;
        }
        case OBJ_NATIVE: {
            FREE(ObjNative, object);
            break;
        }
        case OBJ_STRING: {
            ObjString* string = (ObjString*)object;
            FREE_ARRAY(char, string->chars, string->length + 1);
            FREE(ObjString, object);
            break;
        }
        case OBJ_UPVALUE:
            FREE(ObjUpvalue, object);
            break;
    }
}

void freeObjects() {
    Obj* object = vm.objects;
    while (object != NULL) {
        Obj* next = object->next;
        freeObject(object);
        object = next;
    }
}
