#include "cli.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    if (cli_verify_args(argc, argv) != 0) {
        return -1;
    }

    const int n = atoi(argv[1]);

    for (int i = 0; i < n; i++) {
        if (fork() == 0) {
            printf("Parent PID:\t%d\tCurrent PID:\t%d\n", getppid(), getpid());
            exit(0);
        }
    }

    for (int i = 0; i < n; i++) wait(NULL);
    printf("argv[1]: %d\n", n);

    return 0;
}