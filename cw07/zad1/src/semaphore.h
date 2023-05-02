#ifndef __SEMAPHORE_H__
#define __SEMAPHORE_H__

#include "common.h"
#include <stdbool.h>

int create_semaphore(const char*, int);
int open_semaphore(const char*);
void release(int);
void hold(int);
bool unlink_semaphore(const char*);
bool delete_semaphore(const char*);

#endif // __SEMAPHORE_H__