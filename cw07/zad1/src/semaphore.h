#ifndef __SEMAPHORE_H__
#define __SEMAPHORE_H__

#include "common.h"

int create_semaphore(const char*, int);
int open_semaphore(const char*);
void release(int);
void hold(int);
void smp_close(const char*);

#endif // __SEMAPHORE_H__