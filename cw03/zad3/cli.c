#include "cli.h"
#include <stdio.h>
#include <string.h>
#include <dirent.h>

int cli_verify_args(int argc, char **argv) {
    int flag = 0;

    if (argc < 2) {
        fprintf(stderr, "You passed %d arguments. Too few (at least 2)\n", argc);
        flag = -1;
    }
    if (argc > 1) {
        if (opendir(argv[1]) == NULL) {
            fprintf(stderr, "%s is not a path to directory\n", argv[1]);
            flag = -1;
        }
    }
    if (argc > 2 && strlen(argv[2]) > 255) {
        fprintf(stderr, "\"%s\" is too long (more than 255 characters)\n", argv[2]);
        flag = -1;
    }

    return flag;
}