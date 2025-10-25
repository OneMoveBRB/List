#include <stdio.h>

#include "list_alloc.h"
#include "list_funcs.h"
#include "list_utils.h"

int main() {
    List_t list;

    ListInit(&list);

    ListPushFront(&list, 30);

    ListPushBack(&list, 32);
    ListPushBack(&list, 33);
    ListPushBack(&list, 34);
    ListPushBack(&list, 35);

    ListInsert(&list, 2, 10);
    ListPushFront(&list, 20);

    ListErase(&list, 1);

    ListDump(&list);

    for (size_t i = 0; i < list.arr.size; i++) {
        printf("current counter: %zu\n", GetNode(&list, i));
        printf("value          : %d\n", list.arr.data[GetNode(&list, i)].value);
        printf("\n");
    }

    ListDestroy(&list);

    return 0;
}