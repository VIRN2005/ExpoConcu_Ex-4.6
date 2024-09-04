#include "list.h"
#include <stdio.h>
#include <stdlib.h>

void list_init(list_t *list) {
    list->head = NULL;
    rwlock_init(&list->lock);
}

void list_insert(list_t *list, int data) {
    node_t *node = malloc(sizeof(node_t));
    node->data = data;
    node->next = NULL;

    rwlock_wlock(&list->lock);
    if (list->head == NULL) {
        list->head = node;
    } else {
        node_t *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = node;
    }
    rwlock_wunlock(&list->lock);
}

void list_delete(list_t *list, int data) {
    rwlock_wlock(&list->lock);
    if (list->head == NULL) {
        rwlock_wunlock(&list->lock);
        return;
    }

    if (list->head->data == data) {
        node_t *temp = list->head;
        list->head = list->head->next;
        free(temp);
        rwlock_wunlock(&list->lock);
        return;
    }

    node_t *current = list->head;
    while (current->next != NULL) {
        if (current->next->data == data) {
            node_t *temp = current->next;
            current->next = current->next->next;
            free(temp);
            rwlock_wunlock(&list->lock);
            return;
        }
        current = current->next;
    }

    rwlock_wunlock(&list->lock);
}

void list_print(list_t *list) {
    rwlock_rlock(&list->lock);
    node_t *current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
    rwlock_runlock(&list->lock);
}
