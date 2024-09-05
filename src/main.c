#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "list.h"

// Insert function
void *insert_func(void *arg) {
    list_t *list = (list_t *)arg;
    for (int i = 0; i < 10; i++) {
        list_insert(list, i);
        sleep(1); 
    }
    return NULL;
}

// Delete function
void *delete_func(void *arg) {
    sleep(1);  
    list_t *list = (list_t *)arg;
    for (int i = 0; i < 10; i++) {
        list_delete(list, i);
        sleep(1); 
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