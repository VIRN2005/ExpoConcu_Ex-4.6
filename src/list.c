#include "list.h"
#include <stdio.h>
#include <stdlib.h>

void list_init(List* list) {
    list->head = NULL;
}

void list_insert(List* list, int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = list->head;
    list->head = node;
}

void list_delete(List* list, int data) {
    Node* current = list->head;
    Node* previous = NULL;

    while (current != NULL && current->data != data) {
        previous = current;
        current = current->next;
    }

    if (current != NULL) {
        if (previous == NULL) {
            list->head = current->next;
        } else {
            previous->next = current->next;
        }
        free(current);
    }
}

void list_print(List* list) {
    Node* current = list->head;

    printf("Lista enlazada: ");
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}