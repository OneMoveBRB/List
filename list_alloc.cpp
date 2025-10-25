#include "list_alloc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


ListErr_t ListInit(List_t* list) {
    assert( list != NULL );

    list->arr.size = 0;
    list->arr.capacity = FIRST_SIZE;
    list->arr.data = (Node*)calloc(FIRST_SIZE, sizeof(Node));
    if (list->arr.data == NULL) {
        fprintf(stderr, "Memory allocation error: list->arr.data = NULL\n");
        return LIST_OVERFLOW;
    }

    list->head = 0;
    list->tail = 0;
    list->free = 1;

    for (size_t i = list->free; i < FIRST_SIZE - 1; i++) {
        list->arr.data[i].next = i + 1;
    }   list->arr.data[FIRST_SIZE - 1].next = 0;

    return LIST_OK;
}

ListErr_t ListDestroy(List_t* list) {
    assert( list != NULL );

    list->arr.size = 0;
    list->arr.capacity = 0;
    FREE(list->arr.data);

    list->head = 0;
    list->tail = 0;
    list->free = 0;

    return LIST_OK;
}