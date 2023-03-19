#include "cli.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int cli_verify_args(int argc, char **argv) {
    int flag = 0;

    if (argc < 3) {
        fprintf(stderr, "You passed too few arguments (at least 2)\n");
        flag = -1;
    }
    if (argc > 1) {
        int fd = open(argv[1], O_WRONLY);
        if (fd <= 0) {
            fprintf(stderr, "Input file does not exist\n");
            flag = -1;
        }
        else {
            close(fd);
        }
    }

    return flag;
}