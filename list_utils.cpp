#include "list_utils.h"

#include <stdio.h>

void* MovePtr(void* base, size_t offset, size_t element_size) {
    return (void*)((size_t)base + offset * element_size);
}

size_t GetNode(List_t* list, size_t position) {
    size_t counter = 0;
    size_t curent_pointer = 0;

    if (position < list->arr.size / 2) {
        curent_pointer = list->head;

        for (; counter != position; counter++) {
            curent_pointer = list->arr.data[curent_pointer].next;
        }

    } else {
        curent_pointer = list->tail;
        counter = list->arr.size - 1;

        for (; counter != position; counter--) {
            curent_pointer = list->arr.data[curent_pointer].prev;
        }

    }

    return curent_pointer;
}

void ListDump(List_t* list) {
    FILE* fp = fopen("List_test.txt", "a");
    if (fp == NULL) {
        fprintf(stderr, "Couldn't open  List_test.txt\n");
        return;
    }

    fprintf(fp, "\n############## LIST DUMP ##############\n");
    fprintf(fp, "List size: %zu\nList capacity: %zu\nList data: ", 
                list->arr.size, list->arr.capacity);
    
    for (size_t i = 0; i < list->arr.capacity; i++) {
        fprintf(fp, "%d ", list->arr.data[i].value);
    } fprintf(fp, "\n");

    fprintf(fp, "List next: ");

    for (size_t i = 0; i < list->arr.capacity; i++) {
        fprintf(fp, "%zu ", list->arr.data[i].next);
    } fprintf(fp, "\n");

    fprintf(fp, "List prev: ");

    for (size_t i = 0; i < list->arr.capacity; i++) {
        fprintf(fp, "%zu ", list->arr.data[i].prev);
    } fprintf(fp, "\n");

    fprintf(fp, "List HEAD: %zu\nList TAIL: %zu\nList FREE: %zu\n", 
                list->head, list->tail, list->free);

    return;
}