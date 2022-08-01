#include <stdio.h>
#include <stdlib.h>
#include "doubleLinkedList\doubleLinkedList.h"

int main(int argc, char *argv[])
{
    DoubleLinkedList *mylist = create_list();
    int value = 19;
    int value2 = 24;
    int value3 = 50;
    list_append(mylist, &value);
    list_append(mylist, &value2);
    list_append(mylist, &value3);
    printf("address and value: %p : %d\n", &value, *(int *)list_at(mylist, 0)->value);
    printf("address and value: %p : %d\n", &value2, *(int *)list_at(mylist, 1)->value);
    printf("address and value: %p : %d\n", &value3, *(int *)list_at(mylist, 2)->value);
    printf("list-size: %d\n\n", mylist->size);
    printf("address of first  index: %p\n", list_at(mylist, 0));
    printf("address of second index: %p\n", list_at(mylist, 1));
    printf("address of third  index: %p\n\n", list_at(mylist, 2));

    int *testval = malloc(sizeof(int));
    *testval = 100;
    list_append(mylist, testval);
    printf("size: %d\n", mylist->size);
    // remove last element
    int *torm;
    if (list_remove_at(mylist, mylist->size - 1, (void **)&torm))
    {
        printf("removed %d at %p from the list (%p)\n", *torm, torm, testval);
        free(torm);
        printf("size: %d\n", mylist->size);
    }

    // checking the pointers:

    printf("prev of first:          %p\n", mylist->head->prev);
    printf("address of first index: %p: %d\n", list_at(mylist, 0), *(int *)list_at(mylist, 0)->value);
    printf("next of first:          %p\n\n", mylist->head->next);

    printf("prev of second:          %p\n", list_at(mylist, 1)->prev);
    printf("address of second index: %p: %d\n", list_at(mylist, 1), *(int *)list_at(mylist, 1)->value);
    printf("next of second:          %p\n\n", list_at(mylist, 1)->next);

    printf("prev of third:          %p\n", list_at(mylist, 2)->prev);
    printf("address of third index: %p: %d\n", list_at(mylist, 2), *(int *)list_at(mylist, 2)->value);
    printf("next of third:          %p\n\n", list_at(mylist, 2)->next);

    return 0;
}