#include "dir_browser.h"
#include <ftw.h>
#include <stdio.h>
#include <string.h>

long long total_size = 0;

int handle_ftw(const char *fpath, const struct stat *sb, int tflag) {
    if (!S_ISDIR(sb->st_mode)) {
        printf("%s [%ld B]\n", fpath, sb->st_size);
        total_size += sb->st_size;
    }

    return 0;
}

void db_list_all_files(const char *path) {
    if (ftw(path, handle_ftw, 16) != 0) {
        perror("ftw()");
        return;
    }

    printf("Total size of files: %lld B\n", total_size);
}