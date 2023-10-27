//
// Created by aucker on 10/7/2023.
//
#include <stdlib.h>

#include "compiler.h"
#include "memory.h"
#include "vm.h"

#ifdef DEBUG_LOG_GC
#include <stdio.h>
#include "debug.h"
#endif

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
    if (newSize > oldSize) {
#ifdef DEBUG_STRESS_GC
        collectGarbage();
#endif
    }

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

void markObject(Obj* object) {
    if (object == NULL) return;
#ifdef DEBUG_LOG_GC
    printf("%p mark ", (void*)object);
    printValue(OBJ_VAL(object));
    printf("\n");
#endif

    object->isMarked = true;

    // the capacity is not enough, grow it
    if (vm.grayCapacity < vm.grayCount + 1) {
        vm.grayCapacity = GROW_CAPACITY(vm.grayCapacity);
        vm.grayStack = (Obj**)realloc(vm.grayStack,
                                        sizeof(Obj*) * vm.grayCapacity);

        /*
         * We take responsibility for this array, which includes allocation failure.
         * If we can't create or grow the gray stack, then we can't finish GC
         * This is bad for VM, we just abort here for simplicity.
         *
         * To be more robust, we can allocate a "rainy day fund" block of memory when
         * we start the VM. If the gray stack allocation fails, we free the rainy day
         * block and try again. That may give us enough wiggle room on the heap to
         * create the gray stack, finish the GC, and free up more memory.
         */
        if (vm.grayStack == NULL) exit(1);
    }

    vm.grayStack[vm.grayCount++] = object;
}

void markValue(Value value) {
    // we only care about the heap allocated value, not [numbers, Boolean, nil]
    // cause they are inline in Value, requires no heap allocation.
    if (IS_OBJ(value)) markObject(AS_OBJ(value));
}

static void freeObject(Obj* object) {
#ifdef DEBUG_LOG_GC
    printf("%p free type %d\n", (void*)object, object->type);
#endif

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

static void markRoots() {
    for (Value* slot = vm.stack; slot < vm.stackTop; slot++) {
        markValue(*slot);
    }

    for (int i = 0; i < vm.frameCount; i++) {
        markObject((Obj*)vm.frames[i].closure);
    }

    for (ObjUpvalue* upvalue = vm.openUpvalues;
         upvalue != NULL;
         upvalue = upvalue->next) {
        markObject((Obj*)upvalue);
    }

    markTable(&vm.globals);
    // to keep compiler module cleanly separated from the
    // rest of the VM, we handle in a separate function
    markCompilerRoots();
}

void collectGarbage() {
#ifdef DEBUG_LOG_GC
    printf("-- gc begin\n");
#endif

    markRoots();

#ifdef DEBUG_LOG_GC
    printf("-- gc end\n");
#endif
}

void freeObjects() {
    Obj* object = vm.objects;
    while (object != NULL) {
        Obj* next = object->next;
        freeObject(object);
        object = next;
    }

    // free gray stack when VM shuts down
    free(vm.grayStack);
}
