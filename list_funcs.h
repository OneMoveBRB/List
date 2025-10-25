#ifndef LIST_FUNCS_H
#define LIST_FUNCS_H

#include "list_settings.h"

ListErr_t ListPushFront(List_t* list, int value);
ListErr_t ListPushBack(List_t* list, int value);
ListErr_t ListInsert(List_t* list, size_t position, int value);
ListErr_t ListErase(List_t* list, size_t position);

#endif