#include "cli.h"
#include <stdio.h>
#include <dirent.h>

int cli_verify_args(int argc, char **argv) {
    int flag = 0;

    if (argc < 3) {
        fprintf(stderr, "You passed too few arguments (at least 2)\n");
        flag = -1;
    }
    if (argc > 1) {
        if (opendir(argv[1]) == NULL) {
            fprintf(stderr, "First argument is not a path to directory\n");
            flag = -1;
        }
    }
    if (argc > 2 || strlen(argv[1]) > 255) {
        fprintf(stderr, "Second argument is too long (more than 255 characters)\n");
        flag = -1;
    }

    return flag;
}