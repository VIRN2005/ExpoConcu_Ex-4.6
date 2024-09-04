#include "rwlock.h"
#include <pthread.h>

void rwlock_init(RWLock* lock) {
    lock->readers = 0;
    lock->writers = 0;
    pthread_mutex_init(&lock->mutex, NULL);
    pthread_cond_init(&lock->cond, NULL);
}

void rwlock_read_lock(RWLock* lock) {
    pthread_mutex_lock(&lock->mutex);
    while (lock->writers > 0) {
        pthread_cond_wait(&lock->cond, &lock->mutex);
    }
    lock->readers++;
    pthread_mutex_unlock(&lock->mutex);
}

void rwlock_read_unlock(RWLock* lock) {
    pthread_mutex_lock(&lock->mutex);
    lock->readers--;
    if (lock->readers == 0) {
        pthread_cond_signal(&lock->cond);
    }
    pthread_mutex_unlock(&lock->mutex);
}

void rwlock_write_lock(RWLock* lock) {
    pthread_mutex_lock(&lock->mutex);
    while (lock->readers > 0 || lock->writers > 0) {
        pthread_cond_wait(&lock->cond, &lock->mutex);
    }
    lock->writers++;
    pthread_mutex_unlock(&lock->mutex);
}

void rwlock_write_unlock(RWLock* lock) {
    pthread_mutex_lock(&lock->mutex);
    lock->writers--;
    pthread_cond_broadcast(&lock->cond);
    pthread_mutex_unlock(&lock->mutex);
}