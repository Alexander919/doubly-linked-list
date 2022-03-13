#ifndef LIST_H_SENTRY
#define LIST_H_SENTRY

#include <stdlib.h>
#include <stdio.h>

#define MEM_MSG "Failed to allocate memory."
#define NULL_MSG "Value can't be NULL"

struct Node;
/* doubly linked list */
typedef struct Node {
    struct Node *next;
    struct Node *prev;
    void *value;
} Node;

typedef struct List {
    Node *first;
    Node *last;
    int length;
} List;

typedef void (*printer)(void *); /* knows how to print a value */
typedef int (*compare)(void *, void *); /* knows how to compare two values */

List *create();
void clear(List *list);
void print_list(List *list, printer foo);
void memory_check(void *mem, char *msg);
void insert_sorted(List *list, void *value, compare cmp);
void push_last(List *list, void *value);
void push_first(List *list, void *value);
void *pop_last(List *list);
void *pop_first(List *list);
void *delete_node(List *list, Node *node);

#endif
