#include "dir_browser.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

void db_list_all_files() {
    long long total_size = 0;
    DIR *dir = opendir(".");
    struct dirent *file;
    struct stat f_stat;

    while ((file = readdir(dir)) != NULL) {
        char path[128] = "./";
        strcat(path, file->d_name);
        stat(path, &f_stat);
        if (!S_ISDIR(f_stat.st_mode)) {
            printf("%s [%ld B]\n", file->d_name, f_stat.st_size);
            total_size += f_stat.st_size;
        }
    }

    printf("Total size of files: %lld B\n", total_size);

    closedir(dir);
}