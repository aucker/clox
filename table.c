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
    Entry* tombstone = NULL;

    for (;;) {
        Entry* entry = &entries[index];
        // we probe a sequence during a lookup, we hit the tombstone,
        // we note this is a tombstone and we keeping
        if (entry->key == NULL) {
            if (IS_NIL(entry->value)) {
                // empty entry
                return tombstone != NULL ? tombstone : entry;
            } else {
                // we found the tombstone
                if (tombstone == NULL) tombstone = entry;
            }
        } else if (entry->key == key) {
            // we found the key
            return entry;
        }
        if (entry->key == key || entry->key == NULL) {
            return entry;
        }

        index = (index + 1) % capacity;
    }
}

bool tableGet(Table* table, ObjString* key, Value* value) {
    if (table->count == 0) return false;  // this table is empty

    Entry* entry = findEntry(table->entries, table->capacity, key);
    if (entry->key == NULL) return false;

    *value = entry->value;
    return true;
}

static void adjustCapacity(Table* table, int capacity) {
    Entry* entries = ALLOCATE(Entry, capacity);
    for (int i = 0; i < capacity; i++) {
        entries[i].key = NULL;
        entries[i].value = NIL_VAL;
    }

    table->count = 0;
    for (int i = 0; i < table->capacity; i++) {
        Entry* entry = &table->entries[i];
        if (entry->key == NULL) continue;

        Entry* dest = findEntry(entries, capacity, entry->key);
        dest->key = entry->key;
        dest->value = entry->value;
        table->count++;
    }

    FREE_ARRAY(Entry, table->entries, table->capacity);
    table->entries = entries;
    table->capacity = capacity;
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
//    if (isNewKey) table->count++;
    // this time we also count the tombstone into account
    if (isNewKey && IS_NIL(entry->value)) table->count++;

    entry->key = key;
    entry->value = value;
    return isNewKey;
}

// we add a tombstone when we delete the k/v pair
bool tableDelete(Table* table, ObjString* key) {
    if (table->count == 0) return false;  // this table is empty

    // find the entry
    Entry* entry = findEntry(table->entries, table->capacity, key);
    if (entry->key == NULL) return false;

    // place a tombstone in the deleted entry
    entry->key = NULL;
    entry->value = BOOL_VAL(true);  // this tombstone
    return true;
}

// copy all entries of one hash table into another
void tableAddAll(Table* from, Table* to) {
    for (int i = 0; i < from->capacity; i++) {
        Entry* entry = &from->entries[i];
        if (entry->key != NULL) {
            tableSet(to, entry->key, entry->value);
        }
    }
}

/*
 * it appears we have copy-pasted `findEntry()`. There is a lot of redundancies,
 * but also a couple of key differences. First, we pass in the raw character array
 * of the key we're looking for instead of an ObjString. At the point that we call
 * this, we haven't created an ObjString yet.
 *
 * Second, when checking to see if we found the key, we look at the actual strings.
 * We first see if they have matching lengths and hashes. Those are quick to check
 * and if they aren't equal, the strings definitely aren't the same.
 *
 * If there is a hash collision, we do an actual character-by-character string
 * comparison. This is the one place in the VM where we actually test strings
 * for textual equality. We do it here to deduplicate strings and then the rest
 * of the VM can take for granted that any two strings at different addresses
 * in memory must have different contents.
 */
ObjString* tableFindString(Table* table, const char* chars,
                           int length, uint32_t hash) {
    if (table->count == 0) return NULL;  // the table is empty

    uint32_t index = hash % table->capacity;
    for (;;) {
        Entry* entry = &table->entries[index];
        if (entry->key == NULL) {
            // stop if we find an empty non-tombstone entry
            if (IS_NIL(entry->value)) return NULL;
        } else if (entry->key->length == length &&
                   entry->key->hash == hash &&
                   memcmp(entry->key->chars, chars, length) == 0) {
            // we just found it
            return entry->key;
        }

        index = (index + 1) % table->capacity;
    }
}