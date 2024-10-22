#ifndef LIST_H
#define LIST_H

#include "rwlock.h"

typedef struct node {
    int data;
    struct node *next;
} node_t;

typedef struct {
    node_t *head;
    rwlock_t lock;
} list_t;

void list_init(list_t *list);
void list_insert(list_t *list, int data);
void list_delete(list_t *list, int data);
void list_print(list_t *list);

#endif
