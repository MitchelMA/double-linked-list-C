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
        DoubleLinkedListNode *next = head->next;
        *out = head->value;

        if (next != NULL)
        {
            next->prev = NULL;
        }
        list->head = next;
        free(head);
        list->size--;
        return 1;
    }

    // other indices
    DoubleLinkedListNode *node = list_at(list, index);
    if (node == NULL)
    {
        *out = NULL;
        return 0;
    }
    DoubleLinkedListNode *next = node->next;
    DoubleLinkedListNode *prev = node->prev;

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
    list->size--;
    return 1;
}

int list_insert_before(DoubleLinkedList *list, void *value, unsigned long long index)
{
    if (list == NULL || list->head == NULL || value == NULL)
    {
        return 0;
    }

    if (index == 0)
    {
        DoubleLinkedListNode *head = list->head;
        DoubleLinkedListNode *tmp = malloc(sizeof(DoubleLinkedListNode));
        if (tmp == NULL)
        {
            return 0;
        }
        tmp->next = head;
        tmp->prev = NULL;
        tmp->value = value;

        head->prev = tmp;
        list->head = tmp;
        list->size++;
        return 1;
    }

    DoubleLinkedListNode *node = list_at(list, index);
    if (node == NULL)
    {
        return 0;
    }
    DoubleLinkedListNode *prev = node->prev;

    DoubleLinkedListNode *tmp = malloc(sizeof(DoubleLinkedListNode));
    if (tmp == NULL)
    {
        return 0;
    }

    tmp->value = value;
    tmp->next = node;
    tmp->prev = prev;
    if (prev != NULL)
    {
        prev->next = tmp;
    }
    node->prev = tmp;
    list->size++;

    return 1;
}

int list_insert_after(DoubleLinkedList *list, void *value, unsigned long long index)
{
    if (list == NULL || list->head == NULL || value == NULL)
    {
        return 0;
    }

    DoubleLinkedListNode *node = list_at(list, index);
    if (node == NULL)
    {
        return 0;
    }

    DoubleLinkedListNode *next = node->next;

    DoubleLinkedListNode *tmp = malloc(sizeof(DoubleLinkedListNode));
    if (tmp == NULL)
    {
        return 0;
    }

    tmp->value = value;
    tmp->prev = node;
    tmp->next = next;

    if (next != NULL)
    {
        next->prev = tmp;
    }
    node->next = tmp;
    list->size++;
    return 1;
}