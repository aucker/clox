//
// Created by aucker on 10/18/2023.
//

#include <stdlib.h>
#include <string.h>

#include "memory.h"
#include "object.h"
#include "table.h"
#include "value.h"

#define TABLE_MAX_LOAD 0.75

void initTable(Table* table) {
    table->count = 0;
    table->capacity = 0;
    table->entries = NULL;
}

void freeTable(Table* table) {
    FREE_ARRAY(Entry, table->entries, table->capacity);
    initTable(table);
}

static Entry* findEntry(Entry* entries, int capacity,
                        ObjString* key) {
    uint32_t index = key->hash % capacity;
    for (;;) {
        Entry* entry = &entries[index];
        if (entry->key == key || entry->key == NULL) {
            return entry;
        }

        index = (index + 1) % capacity;
    }
}

// We put the string object into hash tables
bool tableSet(Table* table, ObjString* key, Value value) {
    /*
     * before insert, check we have an array, and that's big enough
     */
    if (table->count + 1 > table->capacity * TABLE_MAX_LOAD) {
        int capacity = GROW_CAPACITY(table->capacity);
        adjustCapacity(table, capacity);
    }

    Entry* entry = findEntry(table->entries, table->capacity, key);
    bool isNewKey = entry->key == NULL;
    if (isNewKey) table->count++;

    entry->key = key;
    entry->value = value;
    return isNewKey;
}