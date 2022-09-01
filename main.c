#include <stdio.h>
#include <stdlib.h>
#include "doubleLinkedList\doubleLinkedList.h"

void undefined_behavior(DoubleLinkedList *list);

int main(int argc, char *argv[])
{
    DoubleLinkedList *mylist = create_list();
    int value = 19;
    int value2 = 24;
    int value3 = 50;
    list_append(mylist, &value);
    list_push(mylist, &value2);
    list_append(mylist, &value3);
    printf("address and value: %p : %d\n", &value2, *(int *)list_at(mylist, 0)->value);
    printf("address and value: %p : %d\n", &value, *(int *)list_at(mylist, 1)->value);
    printf("address and value: %p : %d\n", &value3, *(int *)list_at(mylist, 2)->value);
    printf("list-size: %d\n\n", mylist->size);
    printf("address of first  index: %p\n", list_at(mylist, 0));
    printf("address of second index: %p\n", list_at(mylist, 1));
    printf("address of third  index: %p\n\n", list_at(mylist, 2));

    int *testval = malloc(sizeof(int));
    *testval = 100;
    // list_append(mylist, testval);
    list_insert_after(mylist, testval, 0);
    printf("size: %d\n", mylist->size);
    // remove last element
    int *torm;
    if (list_remove_tail(mylist, (void **)&torm))
    {
        printf("removed %d at %p from the list\n", *torm, torm, testval);
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

    // but it can also be done with c-strings
    DoubleLinkedList *clist = create_list();
    char *first = "This is a c-string in the double linked-list";
    list_append(clist, first);
    printf("%p : %s\n", clist->head->value, (char *)clist->head->value);

    // or a float
    DoubleLinkedList *flist = create_list();
    float myfloat = 9.7f;
    list_append(flist, &myfloat);
    printf("%p : %f\n", flist->head->value, *(float *)flist->head->value);

    // or a list in a list
    DoubleLinkedList *dlist = create_list();
    list_append(dlist, mylist);
    // DoubleLinkedListNode *dlistval = ((DoubleLinkedList *)dlist->head->value)->head->next;
    DoubleLinkedListNode *dlistval = list_at(list_at(dlist, 0)->value, 1);
    int newval = 9;
    *(int *)dlistval->value = newval;
    printf("first index of the first index: %p (%p) : %d\n\n", dlistval, list_at(mylist, 1), *(int *)list_at(mylist, 1)->value);
    // although this obviously shows difficult
    // cause when you go out of bounds, the program segfaults (and this is easy to do)

    // And it is not recommended to have different types together in one list

    // undefined behavior:
    // using stack allocated variables after the end of their scope
    // first create a list
    DoubleLinkedList *undefined = create_list();
    // call a function with undefined behavior
    undefined_behavior(undefined);
    // try to set a different value
    *(int *)list_at(undefined, 3)->value = 0x80;
    // loop through the list to see their addresses and values
    DoubleLinkedListNode *current = undefined->head;
    while (current != NULL)
    {
        // after dereferencing the first time, the value is unpredictable
        printf("address: %p; value: %d\n", current->value, *(int *)current->value);
        current = current->next;
    }

    return 0;
}

void undefined_behavior(DoubleLinkedList *list)
{
    for (int i = 0; i < 10; i++)
    {
        int test = 5;
        list_append(list, &test);
        // this is undefined behavior, because `test` is dropped from the stack here
        // thus all the addresses should be the same
    }
}