#ifndef LIST_UTILS_H
#define LIST_UTILS_H

#include "list_settings.h"

void* MovePtr(void* base, size_t offset, size_t element_size);
size_t GetNode(List_t* list, size_t position);
void ListDump(List_t* list);

#endif