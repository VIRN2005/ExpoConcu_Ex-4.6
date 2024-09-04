#ifndef RWLOCK_H
#define RWLOCK_H

#include <pthread.h>

// Read-Write Lock structure
typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t read_cond, write_cond;
    int readers, writers;
} rwlock_t;

void rwlock_init(rwlock_t *lock);
void rwlock_rlock(rwlock_t *lock);
void rwlock_runlock(rwlock_t *lock);
void rwlock_wlock(rwlock_t *lock);
void rwlock_wunlock(rwlock_t *lock);

#endif // RWLOCK_H
