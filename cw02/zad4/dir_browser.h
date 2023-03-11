#ifndef _DIR_BROWSER_H
#define _DIR_BROWSER_H

#include <sys/stat.h>

int handle_ftw(const char *, const struct stat *, int);
void db_list_all_files(const char *);

#endif // _DIR_BROWSER_H