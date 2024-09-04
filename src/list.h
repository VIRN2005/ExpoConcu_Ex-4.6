#ifndef LIST_H
#define LIST_H

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
} List;

void list_init(List* list);
void list_insert(List* list, int data);
void list_delete(List* list, int data);
void list_print(List* list);

#endif  // LIST_H