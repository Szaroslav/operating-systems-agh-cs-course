#ifndef __SHARED_MEM_H__
#define __SHARED_MEM_H__

#include <stdbool.h>

int create_shared_mem(const char*, int);
int open_shared_mem(const char*);
char* attach_shared_mem(const char*, int);
bool detach_shared_mem(char*);
bool delete_shared_mem(const char*);

#endif // __SHARED_MEM_H__