#include "cli.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int cli_verify_args(int argc, char **argv) {
    int flag = 0;

    if (argc < 5) {
        fprintf(stderr, "You passed too few arguments (at least 4)\n");
        flag = -1;
    }
    if (argc > 1 && strlen(argv[1]) > 1) {
        fprintf(stderr, "First argument is not a char\n");
        flag = -1;
    }
    if (argc > 2 && strlen(argv[2]) > 1) {
        fprintf(stderr, "Second argument is not a char\n");
        flag = -1;
    }
    if (argc > 3) {
        int fd = open(argv[3], O_WRONLY);
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