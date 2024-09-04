#ifndef RWLOCK_H
#define RWLOCK_H

typedef struct RWLock {
    int readers;
    int writers;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} RWLock;

void rwlock_init(RWLock* lock);
void rwlock_read_lock(RWLock* lock);
void rwlock_read_unlock(RWLock* lock);
void rwlock_write_lock(RWLock* lock);
void rwlock_write_unlock(RWLock* lock);

#endif  // RWLOCK_H