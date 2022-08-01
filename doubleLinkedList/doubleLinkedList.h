#ifndef __DOUBLE_LINKED_LIST_H__
#define __DOUBLE_LINKED_LIST_H__

typedef struct DoubleLinkedList DoubleLinkedList;
typedef struct DoubleLinkedListNode DoubleLinkedListNode;

struct DoubleLinkedList
{
    unsigned long long size;
    DoubleLinkedListNode *head;
    DoubleLinkedListNode *tail;
};

struct DoubleLinkedListNode
{
    void *value;
    DoubleLinkedListNode *prev;
    DoubleLinkedListNode *next;
};

DoubleLinkedList *create_list();
int list_append(DoubleLinkedList *list, void *value);
int list_push(DoubleLinkedList *list, void *value);
int list_insert_before(DoubleLinkedList *list, void *value, unsigned long long index);
int list_insert_after(DoubleLinkedList *list, void *value, unsigned long long index);
DoubleLinkedListNode *list_at(DoubleLinkedList *list, unsigned long long index);

int list_remove_at(DoubleLinkedList *list, unsigned long long index, void **out);
int list_remove_head(DoubleLinkedList *list, void **oldheadvalue);
int list_remove_tail(DoubleLinkedList *list, void **oldtailvalue);

#endif // __DOUBLE_LINKED_LIST_H__