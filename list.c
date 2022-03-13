#include "list.h"

void print_list(List *list, printer foo)
{
    Node *cur;
    memory_check(list, NULL_MSG);
    for(cur = list->first; cur; cur = cur->next) {
        foo(cur->value); /* foo function knows how to print the value */
    }
}
/* create a List */
List *create() {
    List *list = calloc(1, sizeof(List));
    memory_check(list, MEM_MSG);

    return list;
}
/* remove a List from memory */
void clear(List *list)
{
    memory_check(list, NULL_MSG);
    Node *first = list->first;
    if(first) {
        first = first->next; /* move to the second node */
        while(first) {
            free(first->prev); /* remove previous node */
            first = first->next;
        }
        free(list->last); /* we still have one node left*/
        list->last = NULL;
    }
    free(list);
}

void memory_check(void *mem, char *msg)
{
    if(!mem) {
        fprintf(stderr, "%s\n", msg);
        exit(1);
    }
}
/* sorting a list is a bad idea(very slow)
 * this function is a lesser evil
 * it inserts elements in the sorted order
 * we find an element that is larger(according to a comparator function)
 * and insert a new node before it
 */
void insert_sorted(List *list, void *value, compare cmp)
{
    /* empty list */
    if(!list->first && !list->last) {
        push_last(list, value);
        return;
    }

    if(cmp(list->first->value, value) >= 0) { /* first element in list is larger then value - insert new value before the first */
        push_first(list, value);
    } else if(cmp(list->last->value, value) <= 0) { /* last element in list is less then value - insert new value after the last */
        push_last(list, value);
    } else { /* the last element is > than the new value => there can be a smaller value that is < last but > new value*/
        for(Node *cur = list->first; cur; cur = cur->next) { /* element is somewhere in the middle */
            if(cmp(cur->value, value) >= 0) { /* the value of the current node is larger then new value - insert new value before current */
                Node *node = calloc(1, sizeof(Node));
                memory_check(node, MEM_MSG);
                node->value = value;
                /* setup the references */
                node->next = cur;
                node->prev = cur->prev;

                cur->prev->next = node;
                cur->prev = node;
                break; /* element inserted - exit */
            }
        }
    }
}
/* push to the end of a list */
void push_last(List *list, void *value)
{
    Node *node = calloc(1, sizeof(Node));
    memory_check(node, MEM_MSG);

    node->value = value;

    if(!list->first && !list->last) {
        list->first = list->last = node;
    } else {
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
    }

    list->length += 1;
}
/* pop from the end of a list */
void *pop_last(List *list)
{
    Node *node = list->last;
    return !node ? NULL : delete_node(list, node);
}
/* push to the beginning of a list */
void push_first(List *list, void *value)
{
    Node *node = calloc(1, sizeof(Node));
    memory_check(node, MEM_MSG);

    node->value = value;

    if(!list->first && !list->last) {
        list->first = list->last = node;
    } else {
        node->next = list->first;
        list->first->prev = node;
        list->first = node;
    }

    list->length += 1;
}
/* pop from the beginning of a list */
void *pop_first(List *list)
{
    Node *node = list->first;
    return !node ? NULL : delete_node(list, node);
}
/* delete any node from a List */
void *delete_node(List *list, Node *node)
{
    void *value = NULL;
    /* if any is NULL just return NULL */
    if(!list->first || !list->last || !node) {
        goto end;
    }

    value = node->value;

    if(list->first == node && list->last == node) { /* the only element */
        list->first = list->last = NULL;
    } else if(list->first == node) { /* the first element */
        list->first = list->first->next;
        list->first->prev = NULL;
    } else if(list->last == node) { /* the last element */
        list->last = list->last->prev;
        list->last->next = NULL;
    } else { /* in the middle */
        /* setup the references */
        Node *after = node->next;
        Node *before = node->prev;

        before->next = after; /* node before the deleted node now points to the one after the deleted node */
        after->prev = before; /* node after the deleted node now points to the one before the deleted node */
    }

    list->length -= 1;
    free(node);
end:
    return value;
}
