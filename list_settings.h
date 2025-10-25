#ifndef LIST_SETTINGS_H
#define LIST_SETTINGS_H

#include <stddef.h>

#define FREE(ptr) free(ptr); ptr = NULL;

const int FIRST_SIZE    = 8;
const int UNINITIALIZED = 0xBAD;

struct Node {
    int value;
    size_t next;
    size_t prev;
};

struct Nodes {
    Node* data;
    size_t size;
    size_t capacity;
};

struct List_t {
    Nodes  arr;
    size_t head;
    size_t tail;
    size_t free;
};

enum ListErr_t {
    LIST_OK,
    LIST_OVERFLOW
};


#endif