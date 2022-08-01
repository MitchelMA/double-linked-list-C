#include <stdlib.h>
#include <stdio.h>
#include "doubleLinkedList.h"

// LOCAL PROTOTYPES //

int _node_append_end_linkage(DoubleLinkedListNode *node, void *value, DoubleLinkedListNode **out);

// END LOCAL PROTOTYPES //

DoubleLinkedList *create_list()
{
    DoubleLinkedList *tmp = malloc(sizeof(DoubleLinkedList));
    if (tmp == NULL)
    {
        return NULL;
    }
    tmp->head = NULL;
    tmp->tail = NULL;
    tmp->size = 0;
    return tmp;
}

int _node_append_end_linkage(DoubleLinkedListNode *node, void *value, DoubleLinkedListNode **out)
{
    if (node == NULL || value == NULL)
    {
        *out = NULL;
        return 0;
    }

    // base case
    if (node->next == NULL)
    {
        DoubleLinkedListNode *tmp = malloc(sizeof(DoubleLinkedListNode));
        if (tmp == NULL)
        {
            *out = NULL;
            return 0;
        }
        tmp->prev = node;
        tmp->next = NULL;
        tmp->value = value;

        node->next = tmp;
        *out = tmp;
        return 1;
    }

    return _node_append_end_linkage(node->next, value, out);
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
        list->tail = tmp;
        list->size++;
        return 1;
    }

    DoubleLinkedListNode *totail;
    int result = _node_append_end_linkage(list->head, value, &totail);
    if (result)
    {
        list->tail = totail;
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

    // optimizing by differentiating between "near end" and "near begin"
    if (index > list->size / 2)
    {
        DoubleLinkedListNode *current = list->tail;
        int cur = list->size;
        while (current != NULL && cur < index)
        {
            current = current->prev;
            cur--;
        }
        return current;
    }
    else
    {
        DoubleLinkedListNode *current = list->head;
        while (current != NULL && index > 0)
        {
            current = current->next;
            index--;
        }

        return current;
    }
    return NULL;
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
    else if (next == NULL && prev != NULL)
    {
        // means that `node` was the tail
        list->tail = prev;
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

    // when its at the end of the list (the tail)
    if (tmp->next == NULL)
    {
        list->tail = tmp;
    }
    return 1;
}