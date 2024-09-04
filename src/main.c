#include "list.h"
#include "rwlock.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

List list;
RWLock lock;

void* insert_thread(void* arg) {
    int i;
    for (i = 0; i < 5; i++) {
        rwlock_write_lock(&lock);
        list_insert(&list, i);
        printf("Hilo de inserción insertando nodo %d...\n", i);
        list_print(&list);
        rwlock_write_unlock(&lock);
    }
    return NULL;
}

void* delete_thread(void* arg) {
    int i;
    for (i = 0; i < 5; i++) {
        rwlock_write_lock(&lock);
        list_delete(&list, i);
        printf("Hilo de eliminación eliminando nodo %d...\n", i);
        list_print(&list);
        rwlock_write_unlock(&lock);
    }
    return NULL;
}

int main() {
    list_init(&list);
    rwlock_init(&lock);

    pthread_t insert_tid, delete_tid;
    pthread_create(&insert_tid, NULL, insert_thread, NULL);
    pthread_create(&delete_tid, NULL, delete_thread, NULL);

    pthread_join(insert_tid, NULL);
    pthread_join(delete_tid, NULL);

    list_print(&list);

    return 0;
}
   