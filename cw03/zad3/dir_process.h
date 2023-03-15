#ifndef _DIR_PROCESS_H
#define _DIR_PROCESS_H

#include <stdbool.h>
#include <sys/stat.h>

void list_all_files_by_content(char *, const char *);
bool file_contains(char *, const char *);

#endif // _DIR_PROCESS_H