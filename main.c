#include <stdio.h>
#include "list.h"

typedef struct task {
    char *name;
    int tid;
    int priority;
    int burst;
} Task;

void foo(void *task)
{
    Task *t = (Task *) task;
    printf("%s %d %d\n", t->name, t->priority, t->burst);
}

int cb(void *a, void *b)
{
    Task *t1 = (Task *) a;
    Task *t2 = (Task *) b;

    return t1->priority - t2->priority;
}

int main(int argc, char **argv)
{
    List *list = create();

    Task *t1 = calloc(1, sizeof(Task));
    Task *t2 = calloc(1, sizeof(Task));
    Task *t3 = calloc(1, sizeof(Task));
    Task *t4 = calloc(1, sizeof(Task));
    t1->name = "T1";
    t1->priority = 3;
    t1->burst = 20;

    t2->name = "T2";
    t2->priority = 1;
    t2->burst = 15;

    t3->name = "T3";
    t3->priority = 6;
    t3->burst = 18;

    t4->name = "T4";
    t4->priority = 2;
    t4->burst = 10;

    insert_sorted(list, t3, cb);
    insert_sorted(list, t1, cb);
    insert_sorted(list, t2, cb);
    insert_sorted(list, t4, cb);

    print_list(list, foo);

    clear(list);
    free(t1);
    free(t2);
    free(t3);
    free(t4);
    return 0;
}
