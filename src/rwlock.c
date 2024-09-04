#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "rwlock.h"

// Initialize the read-write lock
void rwlock_init(rwlock_t *lock) {
    pthread_mutex_init(&lock->mutex, NULL);
    pthread_cond_init(&lock->read_cond, NULL);
    pthread_cond_init(&lock->write_cond, NULL);
    lock->readers = 0;
    lock->writers = 0;
}

// Reader lock
void rwlock_rlock(rwlock_t *lock) {
    pthread_mutex_lock(&lock->mutex);
    printf("Thread %ld requesting read lock...\n", pthread_self());
    while (lock->writers > 0) {
        pthread_cond_wait(&lock->read_cond, &lock->mutex);
    }
    lock->readers++;
    printf("Thread %ld read lock granted.\n", pthread_self());
    pthread_mutex_unlock(&lock->mutex);
}

// Reader unlock
void rwlock_runlock(rwlock_t *lock) {
    pthread_mutex_lock(&lock->mutex);
    lock->readers--;
    if (lock->readers == 0) {
        pthread_cond_signal(&lock->write_cond);
    }
    pthread_mutex_unlock(&lock->mutex);
}

// Writer lock
void rwlock_wlock(rwlock_t *lock) {
    pthread_mutex_lock(&lock->mutex);
    printf("Thread %ld requesting write lock...\n", pthread_self());
    while (lock->readers > 0 || lock->writers > 0) {
        pthread_cond_wait(&lock->write_cond, &lock->mutex);
    }
    lock->writers++;
    printf("Thread %ld write lock granted.\n", pthread_self());
    pthread_mutex_unlock(&lock->mutex);
}

// Writer unlock
void rwlock_wunlock(rwlock_t *lock) {
    pthread_mutex_lock(&lock->mutex);
    lock->writers--;
    if (lock->writers == 0) {
        pthread_cond_broadcast(&lock->read_cond);
    }
    pthread_cond_signal(&lock->write_cond);
    pthread_mutex_unlock(&lock->mutex);
}
