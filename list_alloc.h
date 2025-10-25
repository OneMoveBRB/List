#ifndef LIST_ALLOC_H
#define LIST_ALLOC_H

#include "list_settings.h"

ListErr_t ListInit(List_t* list);
ListErr_t ListDestroy(List_t* list);

#endif