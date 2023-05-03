#ifndef __SEMAPHORE_H__
#define __SEMAPHORE_H__

#include "common.h"
#include <stdbool.h>
#include <semaphore.h>

#ifdef SYSTEMV
    typedef int semaphore_t;
#endif // SYSTEMV
#ifdef POSIX
    typedef sem_t* semaphore_t;
#endif // POSIX

semaphore_t create_semaphore(const char*, int);
semaphore_t open_semaphore(const char*);
void release(semaphore_t);
void hold(semaphore_t);
bool close_semaphore(semaphore_t);
bool delete_semaphore(const char*);

#endif // __SEMAPHORE_H__