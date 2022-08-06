#include <stdlib.h>
#include <stdio.h>
#include "doubleLinkedList.h"

// LOCAL PROTOTYPES //

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

    DoubleLinkedListNode *tail = list->tail;
    DoubleLinkedListNode *tmp = malloc(sizeof(DoubleLinkedListNode));
    if (tmp == NULL)
    {
        return 0;
    }
    tmp->value = value;

    list->tail->next = tmp;
    list->tail = tmp;
    tmp->next = NULL;
    tmp->prev = tail;
    list->size++;

    return 1;
}

int list_push(DoubleLinkedList *list, void *value)
{
    if (list == NULL || value == NULL)
    {
        return 0;
    }

    if (list->tail == NULL)
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

    DoubleLinkedListNode *head = list->head;
    DoubleLinkedListNode *tmp = malloc(sizeof(DoubleLinkedListNode));
    if (tmp == NULL)
    {
        return 0;
    }

    tmp->value = value;
    tmp->prev = NULL;
    list->head = tmp;
    head->prev = tmp;
    tmp->next = head;
    list->size++;
    return 0;
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

DoubleLinkedListNode *list_at(DoubleLinkedList *list, unsigned long long index)
{
    if (list == NULL || list->head == NULL || index >= list->size || index < 0)
    {
        return NULL;
    }

    // optimizing by differentiating between "near end" and "near begin"
    if (index > list->size / 2)
    {
        DoubleLinkedListNode *current = list->tail;
        int cur = list->size - 1;
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
    if (list == NULL || list->head == NULL || index >= list->size || index < 0)
    {
        *out == NULL;
        return 0;
    }

    // removes the head
    if (index == 0)
    {
        return list_remove_head(list, out);
    }
    // removes the tail
    if (index == list->size - 1)
    {
        return list_remove_tail(list, out);
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
    else
    {
        // means that `node` was the tail
        list->tail = prev;
    }
    if (prev != NULL)
    {
        prev->next = next;
    }
    else
    {
        // means that `node` was the head
        list->head = next;
    }
    list->size--;
    return 1;
}

int list_remove_head(DoubleLinkedList *list, void **oldheadvalue)
{
    if (list == NULL || list->head == NULL)
    {
        *oldheadvalue = NULL;
        return 0;
    }

    DoubleLinkedListNode *head = list->head;
    DoubleLinkedListNode *next = head->next;

    list->head = next;
    if (next != NULL)
    {
        list->head->prev = NULL;
    }
    else
    {
        // head was also the tail
        list->tail = NULL;
    }
    *oldheadvalue = head->value;
    free(head);
    list->size--;
    return 1;
}

int list_remove_tail(DoubleLinkedList *list, void **oldtailvalue)
{
    if (list == NULL || list->tail == NULL)
    {
        *oldtailvalue = NULL;
        return 0;
    }

    DoubleLinkedListNode *tail = list->tail;
    DoubleLinkedListNode *prev = tail->prev;

    list->tail = prev;
    if (prev != NULL)
    {
        list->tail->next = NULL;
    }
    else
    {
        // tail was also the head
        list->head = NULL;
    }

    *oldtailvalue = tail->value;
    free(tail);
    list->size--;
    return 1;
}