#include "signals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

void handle_signal(int signum) {
    printf("Handle signal %d\n", signum);
}

void mask_signal() {
    sigset_t newmask, oldmask;
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGUSR1);
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
        perror("Unable to block a signal\n");
}

void validate_is_signal_pending() {
    sigset_t pending_set;
    sigpending(&pending_set);
    if (sigismember(&pending_set, SIGUSR1) == 1)
        printf("SIGUSR1 is waiting for unlocking...\n");
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Too few arguments (at least 1)\n");
        return -1;
    }

    const enum Signal sig = parse_signal(argv[1]);

    switch (sig) {
        case SIG_IGNORE:
            signal(SIGUSR1, SIG_IGN);
            break;

        case SIG_HANDLER:
            signal(SIGUSR1, handle_signal);
            break;

        case SIG_MASK:
        case SIG_PENDING:
            mask_signal();
            break;
    }
    
    printf("Raise a signal in root process...\n"); 
    raise(SIGUSR1);

    printf("[Root process]\n");
    validate_is_signal_pending();

    if (fork() == 0) {
        if (sig != SIG_PENDING) {
            printf("Raise a signal in child process...\n"); 
            raise(SIGUSR1);
        }

        printf("[Child process]\n");
        validate_is_signal_pending();
    }

    execl("build/exec", "exec", (char *) NULL);

    while (wait(NULL));

    return 0;
}