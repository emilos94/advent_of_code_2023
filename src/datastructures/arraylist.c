#include "arraylist.h"

// forward decl.
void _arraylist_sort(ArrayList* list, int low, int high, int (comparison_func)(void*, void*));
uint32_t _arraylist_sort_partition(ArrayList* list, int low, int high,  int (comparison_func)(void*, void*));
void _arraylist_swap(ArrayList* list, uint32_t i, uint32_t j);


ArrayList* arraylist_create(uint32_t capacity, uint32_t element_byte_size) {
    ArrayList* list = malloc(sizeof(ArrayList));
    list->data = malloc(sizeof(char) * capacity * element_byte_size);
    list->capacity = capacity;
    list->element_byte_size = element_byte_size;
    list->count = 0;
    return list;
}

void arraylist_add(ArrayList* list, void* entry) {
    if (list->count == list->capacity) {
        // realign
        list->capacity *= 2;
        list->data = realloc(list->data, list->capacity * list->element_byte_size);
    }
    
    void* ptr = list->data + (list->count * list->element_byte_size);
    memcpy(ptr, entry, list->element_byte_size);
    list->count++;
}

void* arraylist_push(ArrayList* list) {
    if (list->count == list->capacity) {
        // realign
        list->capacity *= 2;
        list->data = realloc(list->data, list->capacity * list->element_byte_size);
    }
    
    void* ptr = list->data + list->count * list->element_byte_size;
    list->count++;
    return ptr;
}

void* arraylist_get(ArrayList* list, uint32_t index) {
    assert(index < list->count);
    
    return list->data + index * list->element_byte_size;
}

ArrayList* arraylist_copy(ArrayList* list) {
    ArrayList* cpy = arraylist_create(list->capacity, list->element_byte_size);
    cpy->count = list->count;
    memcpy(cpy->data, list->data, list->count * list->element_byte_size);
    return cpy;
}

// Does not keep order of items, but retains a dense array list
void arraylist_remove(ArrayList* list, uint32_t index) {
    assert(index < list->count);

    // decrement count and return if remove last item
    if (index == list->count - 1) {
        list->count--;
        return;
    }

    // move last item to removed index spot
    void* ptr_to_remove = list->data + index * list->element_byte_size;
    void* ptr_last_element = list->data + (list->count-1) * list->element_byte_size;

    memcpy(ptr_to_remove, ptr_last_element, list->element_byte_size);
    list->count--;
}

void* arraylist_popback(ArrayList* list) {
    assert(list->count > 0);

    void* ptr = list->data + (list->count-1) * list->element_byte_size;
    list->count--;
    return ptr;
}

void* arraylist_peekback(ArrayList* list) {
    assert(list->count > 0);

    return list->data + (list->count-1) * list->element_byte_size;
}

void arraylist_free(ArrayList* list) {
    free(list->data);
    free(list);
}


void arraylist_sort(ArrayList* list, int (comparison_func)(void*, void*)) {
    if (list->count <= 1) {
        return;
    }

    _arraylist_sort(list, 0, list->count-1, comparison_func);
}


void _arraylist_sort(ArrayList* list, int low, int high, int (comparison_func)(void*, void*)) {
    if (low >= high || low < 0) {
        return;
    }

    int pivot = _arraylist_sort_partition(list, low, high, comparison_func);
    _arraylist_sort(list, low, pivot - 1, comparison_func);
    _arraylist_sort(list, pivot + 1, high, comparison_func);
}

uint32_t _arraylist_sort_partition(ArrayList* list, int low, int high,  int (comparison_func)(void*, void*)) {
    void* pivot = arraylist_get(list, high);

    int tmp_pivot = low - 1;

    for (int j = low; j < high; j++) {
        int comp = (*comparison_func)(arraylist_get(list, j), pivot);
        uint8_t j_lessthan_eq = comp == -1 || comp == 0;
        if (j_lessthan_eq) {
            tmp_pivot++;
            _arraylist_swap(list, tmp_pivot, j);
        }
    }

    tmp_pivot++;
    _arraylist_swap(list, tmp_pivot, high);
    return tmp_pivot;
}

void _arraylist_swap(ArrayList* list, uint32_t i, uint32_t j) {
    assert(i < list->count && j < list->count);

    if (i == j) {
        return;
    }

    void* tmp = malloc(sizeof(char) * list->element_byte_size);

    void* ptr_i = arraylist_get(list, i);
    void* ptr_j = arraylist_get(list, j);

    memcpy(tmp, ptr_i, list->element_byte_size);
    memcpy(ptr_i, ptr_j, list->element_byte_size);
    memcpy(ptr_j, tmp, list->element_byte_size);

    free(tmp);
}
