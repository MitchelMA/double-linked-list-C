#include <stdio.h>
#include <stdlib.h>
#include "doubleLinkedList\doubleLinkedList.h"

int main(int argc, char *argv[])
{
    DoubleLinkedList *mylist = create_list();
    int value = 9;
    int value2 = 24;
    append_to_list(mylist, &value);
    append_to_list(mylist, &value2);
    printf("address and value: %p : %d\n", &value, *((int *)mylist->head->value));
    printf("address and value: %p : %d\n", &value2, *((int *)mylist->head->next->value));

    return 0;
}