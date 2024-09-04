#include "rwlock.h"
#include <stdio.h>

void rwlock_init(rwlock_t *lock) {
    pthread_mutex_init(&lock->mutex, NULL);
    pthread_cond_init(&lock->read_cond, NULL);
    pthread_cond_init(&lock->write_cond, NULL);
    lock->readers = 0;
    lock->writers = 0;
}

void rwlock_rlock(rwlock_t *lock) {
    pthread_mutex_lock(&lock->mutex);
    while (lock->writers > 0) {
        pthread_cond_wait(&lock->read_cond, &lock->mutex);
    }
    lock->readers++;
    pthread_mutex_unlock(&lock->mutex);
}

void rwlock_runlock(rwlock_t *lock) {
    pthread_mutex_lock(&lock->mutex);
    lock->readers--;
    if (lock->readers == 0) {
        pthread_cond_signal(&lock->write_cond);
    }
    pthread_mutex_unlock(&lock->mutex);
}

void rwlock_wlock(rwlock_t *lock) {
    pthread_mutex_lock(&lock->mutex);
    while (lock->readers > 0 || lock->writers > 0) {
        pthread_cond_wait(&lock->write_cond, &lock->mutex);
    }
    lock->writers++;
    pthread_mutex_unlock(&lock->mutex);
}

void rwlock_wunlock(rwlock_t *lock) {
    pthread_mutex_lock(&lock->mutex);
    lock->writers--;
    pthread_cond_broadcast(&lock->read_cond);
    pthread_cond_signal(&lock->write_cond);
    pthread_mutex_unlock(&lock->mutex);
}
