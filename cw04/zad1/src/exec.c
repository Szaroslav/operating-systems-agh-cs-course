#include <stdio.h>
#include <signal.h>

void validate_is_signal_pending() {
    sigset_t pending_set;
    sigpending(&pending_set);
    printf("[exec]\n");
    if (sigismember(&pending_set, SIGUSR1) == 1)
        printf("SIGUSR1 is waiting for unlocking...\n");
}

int main(int argc, char **argv) {
    validate_is_signal_pending();
    raise(SIGUSR1);

    return 0;
}