#include "cli.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

int cli_verify_args(int argc, char **argv) {
    int flag = 0;

    if (argc < 2) {
        fprintf(stderr, "You passed too few arguments (at least 1)\n");
        flag = -1;
    }
    if (argc > 1) {
        if (opendir(argv[1]) == NULL) {
            fprintf(stderr, "First argument is not a path to directory\n");
            flag = -1;
        }
    }

    return flag;
}

char *get_app_name(char *path) {
    char *last_slash = strrchr(path, '/');
    int n = strlen(path);
    int new_size = n - strlen(last_slash + 1);

    char *name = malloc(sizeof(char) * new_size + 1);
    strncpy(name, last_slash + 1, new_size);
    name[new_size] = '\0';

    return new_size > 0 ? name : NULL;
}