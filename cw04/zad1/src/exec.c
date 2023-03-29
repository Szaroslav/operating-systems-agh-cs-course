#include "signals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

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
        printf("[exec] SIGUSR1 is pending\n");
    else
        printf("[exec] SIGUSR1 is not pending\n");
}

void set_signal(const enum Signal sig) {
    switch (sig) {
        case SIG_IGNORE:
            signal(SIGUSR1, SIG_IGN);
            break;

        case SIG_HANDLER:
            return;

        case SIG_MASK:
            mask_signal();
            break;

        case SIG_PENDING:
            validate_is_signal_pending();
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Too few arguments (at least 1)\n");
        return -1;
    }

    const enum Signal sig = parse_signal(argv[1]); 

    set_signal(sig);
    
    printf("[main.root] Raise a signal\n"); 
    raise(SIGUSR1);

    if (fork() == 0) {
        set_signal(sig);

        if (sig != SIG_PENDING) {
            printf("[main.child] Raise a signal\n"); 
            raise(SIGUSR1);
        }
        else {
            validate_is_signal_pending();
        }
    }

    while (wait(NULL));

    return 0;
}