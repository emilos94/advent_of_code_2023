#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../core/core.h"

typedef struct ArrayList ArrayList;
struct ArrayList {
    uint32_t capacity;
    uint32_t element_byte_size;
    uint32_t count;
    
    void* data;
};

ArrayList* arraylist_create(uint32_t capacity, uint32_t element_byte_size);
void arraylist_add(ArrayList* list, void* entry);
void* arraylist_push(ArrayList* list);
void* arraylist_get(ArrayList* list, uint32_t index);
ArrayList* arraylist_copy(ArrayList* list);
void arraylist_remove(ArrayList* list, uint32_t index);
void* arraylist_popback(ArrayList* list);
void* arraylist_peekback(ArrayList* list);
void arraylist_free(ArrayList* list);
void arraylist_sort(ArrayList* list, int (comparison_func)(void*, void*));
b8 arraylist_anymatch(ArrayList* list, b8 (*predicate)(void*));

#define ARRAYLIST_FOREACH(list, type, name)\
    type* name = 0;\
    int index = 0;\
    for(index = 0, name = arraylist_get(list, index); index < list->count; index++, name = index < list->count ? arraylist_get(list, index) : 0)

#define ARRAYLIST_FOREACHI(list, idx, type, name)\
    type* name = 0;\
    int idx = 0;\
    for(idx = 0, name = arraylist_get(list, idx); idx < list->count; idx++, name = idx < list->count ? arraylist_get(list, idx) : 0)

#endif