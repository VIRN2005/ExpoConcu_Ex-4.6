#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

// Initialize the linked list
void list_init(list_t *list) {
    list->head = NULL;
    rwlock_init(&list->lock);
}

// Insert a node into the linked list
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
    printf("Hilo de inserción insertando nodo %d...\n", data);
    list_print(list);
    rwlock_wunlock(&list->lock);
}

// Delete a node from the linked list
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
        printf("Hilo de eliminación eliminando nodo %d...\n", data);
        list_print(list);
        rwlock_wunlock(&list->lock);
        return;
    }

    node_t *current = list->head;
    while (current->next != NULL) {
        if (current->next->data == data) {
            node_t *temp = current->next;
            current->next = current->next->next;
            free(temp);
            printf("Hilo de eliminación eliminando nodo %d...\n", data);
            list_print(list);
            rwlock_wunlock(&list->lock);
            return;
        }
        current = current->next;
    }

    rwlock_wunlock(&list->lock);
}

// Print the linked list
void list_print(list_t *list) {
    rwlock_rlock(&list->lock);
    printf("Lista enlazada actualizada:\n");
    node_t *current = list->head;
    while (current != NULL) {
        printf("-> Nodo %d\n", current->data);
        current = current->next;
    }
    if (list->head == NULL) {
        printf("Lista vacía.\n");
    }
    printf("\n");
    rwlock_runlock(&list->lock);
}
