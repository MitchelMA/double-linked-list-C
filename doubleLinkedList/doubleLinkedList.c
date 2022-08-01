#include <stdlib.h>
#include <stdio.h>
#include "doubleLinkedList.h"

// LOCAL PROTOTYPES //

int node_append_end_linkage(DoubleLinkedListNode *node, void *value);

// END LOCAL PROTOTYPES //

DoubleLinkedList *create_list()
{
    DoubleLinkedList *tmp = malloc(sizeof(DoubleLinkedList));
    if (tmp == NULL)
    {
        return NULL;
    }
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
        if (tmp == NULL)
        {
            return 0;
        }
        tmp->prev = node;
        tmp->next = NULL;
        tmp->value = value;

        node->next = tmp;
        return 1;
    }

    return node_append_end_linkage(node->next, value);
}

int list_append(DoubleLinkedList *list, void *value)
{
    if (list == NULL || value == NULL)
    {
        return 0;
    }

    if (list->head == NULL)
    {
        DoubleLinkedListNode *tmp = malloc(sizeof(DoubleLinkedListNode));
        if (tmp == NULL)
        {
            return 0;
        }
        tmp->prev = NULL;
        tmp->next = NULL;
        tmp->value = value;

        list->head = tmp;
        list->size++;
        return 1;
    }

    int result = node_append_end_linkage(list->head, value);
    if (result)
    {
        list->size++;
    }
    return result;
}

DoubleLinkedListNode *list_at(DoubleLinkedList *list, unsigned long long index)
{
    if (list == NULL || list->head == NULL)
    {
        return NULL;
    }

    DoubleLinkedListNode *current = list->head;
    while (current != NULL && index > 0)
    {
        current = current->next;
        index--;
    }

    return current;
}

int list_remove_at(DoubleLinkedList *list, unsigned long long index, void **out)
{
    if (list == NULL || list->head == NULL)
    {
        *out == NULL;
        return 0;
    }

    // removes the head
    if (index == 0)
    {
        DoubleLinkedListNode *head = list->head;
        DoubleLinkedListNode *over = list->head->next;
        *out = head->value;

        if (over != NULL)
        {
            over->prev = NULL;
        }
        list->head = over;
        free(head);
        list->size--;
        return 1;
    }

    // other indices
    DoubleLinkedListNode *node = list_at(list, index);
    DoubleLinkedListNode *next = node->next;
    DoubleLinkedListNode *prev = node->prev;
    if (node == NULL)
    {
        *out = NULL;
        return 0;
    }

    *out = node->value;

    free(node);
    if (next != NULL)
    {
        next->prev = prev;
    }
    if (prev != NULL)
    {
        prev->next = next;
    }
    return 1;
}