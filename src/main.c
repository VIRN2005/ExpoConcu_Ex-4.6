#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

// Insert function
void *insert_func(void *arg) {
    list_t *list = (list_t *)arg;
    for (int i = 0; i < 10; i++) {
        list_insert(list, i);
        list_print(list);
        usleep(100000); // Sleep to allow the delete thread to work
    }
    return NULL;
}

// Delete function
void *delete_func(void *arg) {
    list_t *list = (list_t *)arg;
    for (int i = 0; i < 10; i++) {
        list_delete(list, i);
        list_print(list);
        usleep(100000); // Sleep to allow the insert thread to work
    }
    return NULL;
}

int main() {
    list_t list;
    list_init(&list);

    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, insert_func, &list);
    pthread_create(&thread2, NULL, delete_func, &list);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
