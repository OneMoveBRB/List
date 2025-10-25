#include "list_funcs.h"

#include <stdio.h>
#include <assert.h>

#include "list_utils.h"

ListErr_t ListPushBack(List_t* list, int value) {
    assert( list != NULL );

    if (list->head == 0) {
        list->head = list->free;
        list->tail = list->free;
        list->free = list->arr.data[list->free].next;
        list->arr.data[list->head].value = value;
        list->arr.data[list->head].next = 0;
        list->arr.data[list->head].prev = 0;
    } else {
        list->arr.data[list->free].value = value;
        list->arr.data[list->free].prev = list->tail;
        list->arr.data[list->tail].next = list->free;
        list->tail = list->free;
        list->free = list->arr.data[list->tail].next;
        list->arr.data[list->tail].next = 0;
    }

    ++list->arr.size;

    return LIST_OK;
}

ListErr_t ListPushFront(List_t* list, int value) {
    assert( list != NULL );

    if (list->head == 0) {
        ListPushBack(list, value);
        return LIST_OK;
    } else {
        size_t free_position = list->free;

        list->arr.data[free_position].value = value;

        list->free = list->arr.data[free_position].next;

        list->arr.data[free_position].next = list->head;
        list->arr.data[list->head].prev = free_position;
        
        list->arr.data[free_position].prev = 0;
        list->head = free_position;
    }

    ++list->arr.size;

    return LIST_OK;
}

ListErr_t ListInsert(List_t* list, size_t position, int value) {
    assert( list!=NULL );
    assert( 0 <= position && position < list->arr.size );

    if (position == 0) {
        ListPushFront(list, value);
        return LIST_OK;
    } else if (position == list->arr.size - 1) {
        ListPushBack(list, value);
        return LIST_OK;
    }

    size_t logic_position = GetNode(list, position);
    size_t free_position = list->free;

    list->arr.data[free_position].value = value;

    // connection with logic prev
    list->arr.data[free_position].prev = list->arr.data[logic_position].prev;
    list->arr.data[list->arr.data[logic_position].prev].next = free_position;

    // connection with logic next + move list_free to the next one
    list->arr.data[logic_position].prev = free_position;
    
    list->free = list->arr.data[free_position].next;

    list->arr.data[free_position].next = logic_position;

    ++list->arr.size;

    return LIST_OK;
}

ListErr_t ListErase(List_t* list, size_t position) {
    assert( list != NULL );
    assert( 0 <= position && position < list->arr.size );

    if (position == 0) {
        // ListPopBack
    } else if (position == list->arr.size - 1) {
        // ListPopFront
    }

    size_t logic_position = GetNode(list, position);

    list->arr.data[list->arr.data[logic_position].prev].next = list->arr.data[logic_position].next;
    list->arr.data[list->arr.data[logic_position].next].prev = list->arr.data[logic_position].prev;

    list->arr.data[logic_position].next = list->free;
    list->arr.data[logic_position].prev = 0;

    list->free = logic_position;

    --list->arr.size;

    return LIST_OK;
}