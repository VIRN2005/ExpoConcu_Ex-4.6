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
    rwlock_wlock(&list->lock);  // Bloqueo de escritura
    node_t *new_node = malloc(sizeof(node_t));
    if (new_node == NULL) {
        perror("Failed to allocate memory for new node");
        rwlock_wunlock(&list->lock);  // Liberar el bloqueo si hay fallo
        return;
    }
    new_node->data = data;
    new_node->next = list->head;
    list->head = new_node;
    
    printf("Inserting: %d\n", data);  // Imprimir el número insertado

    rwlock_wunlock(&list->lock);  // Liberar el bloqueo de escritura
}

// Delete the first occurrence of an element in the list
void list_delete(list_t *list, int data) {
    rwlock_wlock(&list->lock);  // Bloqueo de escritura
    node_t *current = list->head;
    node_t *prev = NULL;

    while (current != NULL) {
        if (current->data == data) {
            if (prev == NULL) {
                list->head = current->next;  // Eliminar el nodo si es la cabeza
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Deleting: %d\n", data);  // Imprimir el número eliminado
            rwlock_wunlock(&list->lock);  // Liberar el bloqueo de escritura
            return;
        }
        prev = current;
        current = current->next;
    }

    // Si no se encuentra el dato
    printf("Data %d not found\n", data);

    rwlock_wunlock(&list->lock);  // Liberar el bloqueo de escritura
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
