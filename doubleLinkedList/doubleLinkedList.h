#ifndef __DOUBLE_LINKED_LIST_H__
#define __DOUBLE_LINKED_LIST_H__

typedef struct DoubleLinkedList DoubleLinkedList;
typedef struct DoubleLinkedListNode DoubleLinkedListNode;

struct DoubleLinkedList
{
    unsigned long long size;
    DoubleLinkedListNode *head;
};

struct DoubleLinkedListNode
{
    void *value;
    DoubleLinkedListNode *prev;
    DoubleLinkedListNode *next;
};

DoubleLinkedList *create_list();
int append_to_list(DoubleLinkedList *list, void *value);

#endif // __DOUBLE_LINKED_LIST_H__