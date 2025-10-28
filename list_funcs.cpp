#include "list_funcs.h"

#include <stdio.h>
#include <assert.h>

#include "list_utils.h"

ListErr_t ListPushBack(List_t* list, int value) {
    assert( list != NULL );

    if (list->head == 0) {
        Node* free_node  = &list->arr.data[list->free];

        list->head = list->free;
        list->tail = list->free;
        list->free = free_node->next;

        free_node->value = value;
        free_node->next = 0;
        free_node->prev = 0;
    } else {
        size_t free_position = list->free;
        size_t tail_position = list->tail;
        Node*  free_node     = &list->arr.data[free_position];
        Node*  tail_node     = &list->arr.data[tail_position];

        free_node->value = value;

        free_node->prev  = tail_position;
        tail_node->next  = free_position;
        
        list->tail       = free_position;
        list->free       = free_node->next;

        free_node->next  = 0;
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
        size_t next_position = list->head;
        Node*  free_node     = &list->arr.data[free_position];
        Node*  next_node     = &list->arr.data[next_position];

        free_node->value = value;
        
        free_node->next = next_position;
        next_node->prev = free_position;
        
        list->free      = free_node->next;
        list->head      = free_position;
        
        free_node->prev = 0;
    }

    ++list->arr.size;

    return LIST_OK;
}

ListErr_t ListInsert(List_t* list, size_t position, int value) {
    assert( list != NULL );
    assert( position < list->arr.size );

    if (position == 0) {
        ListPushFront(list, value);
        return LIST_OK;
    } else if (position == list->arr.size - 1) {
        ListPushBack(list, value);
        return LIST_OK;
    }

    size_t logic_next_position = GetNode(list, position);
    Node*  logic_next_node     = &list->arr.data[logic_next_position];
    
    size_t free_position       = list->free;
    Node*  free_node           = &list->arr.data[free_position];

    size_t logic_prev_position = logic_next_node->prev;
    Node*  logic_prev_node     = &list->arr.data[logic_prev_position];

    free_node->value = value;

    free_node->prev       = logic_prev_position;
    logic_prev_node->next = free_position;

    logic_next_node->prev = free_position;
    
    list->free = free_node->next;

    free_node->next = logic_next_position;

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
