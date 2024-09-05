#include <stdio.h>
#include <stdlib.h>
#include "list.h"

// Initialize the list
void list_init(list_t *list) {
    list->head = NULL;
    rwlock_init(&list->lock);
}

// Insert a new element at the beginning of the list
void list_insert(list_t *list, int data) {
    rwlock_wlock(&list->lock);  
    node_t *new_node = malloc(sizeof(node_t));
    if (new_node == NULL) {
        perror("Failed to allocate memory for new node");
        rwlock_wunlock(&list->lock); 
        return;
    }
    new_node->data = data;
    new_node->next = list->head;
    list->head = new_node;
    
    printf("Inserting: %d\n", data); 

    rwlock_wunlock(&list->lock);
}

// Delete the first occurrence of an element in the list
void list_delete(list_t *list, int data) {
    rwlock_wlock(&list->lock);
    node_t *current = list->head;
    node_t *prev = NULL;

    while (current != NULL) {
        if (current->data == data) {
            if (prev == NULL) {
                list->head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Deleting: %d\n", data);
            rwlock_wunlock(&list->lock); 
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("Data %d not found\n", data);

    rwlock_wunlock(&list->lock); 
}

// Print the list elements
void list_print(list_t *list) {
    rwlock_rlock(&list->lock);
    
    node_t *current = list->head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");

    rwlock_runlock(&list->lock);
}
