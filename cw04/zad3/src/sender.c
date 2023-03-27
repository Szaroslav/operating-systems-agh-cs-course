#include "mode.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

int success = 0;

void handle_signal(int signo) {
    success = 1;
}

void set_sigaction() {
    struct sigaction act;
    act.sa_handler = handle_signal;
    sigemptyset(&act.sa_mask);

    sigaction(SIGUSR1, &act, NULL);
}

int main(int argc, char **argv) {
    if (argc < 3) {
        perror("[ERROR] At least 2 arguments are required\n");
        return -1;
    }

    int pid = atoi(argv[1]);

    printf("Sender (PID: %d)\n", getpid());
    printf("Catcher's PID: %d\n", pid);

    for (int i = 2; i < argc; i++) {
        const int mode = atoi(argv[i]);
        success = 0;

        set_sigaction();

        sigval_t sigval = {mode};
        sigqueue(pid, SIGUSR1, sigval);
        printf("Sent [mode %d]\n", mode);

        while (!success);

        printf("Received confirmation from catcher [mode %d]\n", mode);
    }

    // printf("\n======== Modes of execution ========\n");
    // printf("[1] Print numbers from 1 to 100\n");
    // printf("[2] Print current time\n");
    // printf("[3] Print number of mode changes\n");
    // printf("[4] Print current time per 1 second until mode changes\n");
    // printf("[5] Exit\n");
    // printf("Enter list of modes separated by spaces (e.g. 3 4 4 2 3 1): ");
    

    return 0;
}