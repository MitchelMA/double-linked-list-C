#include <stdlib.h>
#include "doubleLinkedList.h"

// LOCAL PROTOTYPES //

int node_append_end_linkage(DoubleLinkedListNode *node, void *value);

// END LOCAL PROTOTYPES //

DoubleLinkedList *create_list()
{
    DoubleLinkedList *tmp = malloc(sizeof(DoubleLinkedList));
    tmp->head = NULL;
    tmp->size = 0;
    return tmp;
}

int node_append_end_linkage(DoubleLinkedListNode *node, void *value)
{
    if (node == NULL || value == NULL)
    {
        return 0;
    }

    // base case
    if (node->next == NULL)
    {
        DoubleLinkedListNode *tmp = malloc(sizeof(DoubleLinkedListNode));
        tmp->prev = node;
        tmp->next = NULL;
        tmp->value = value;

        node->next = tmp;
        return 1;
    }

    return node_append_end_linkage(node->next, value);
}

int append_to_list(DoubleLinkedList *list, void *value)
{
    if (list == NULL || value == NULL)
    {
        return 0;
    }

    if (list->head == NULL)
    {
        DoubleLinkedListNode *tmp = malloc(sizeof(DoubleLinkedListNode));
        tmp->prev = NULL;
        tmp->next = NULL;
        tmp->value = value;

        list->head = tmp;
        return 1;
    }

    return node_append_end_linkage(list->head, value);
}