#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <wait.h>


void signal_info_handler(int sig, siginfo_t* info, void* ucontext) {
    printf("=======================================\n");
    printf("Signal number: %d\n", info->si_signo);
    printf("Signal has been sent by process %d\n", info->si_pid);
}

void signal_data_info_handler(int sig, siginfo_t* info, void* ucontext) {
    signal_info_handler(sig, info, ucontext);
    printf("Integer data sent %d\n", info->si_value.sival_int);
}

void signal_child_info_handler(int sig, siginfo_t* info, void* ucontext) {
    signal_info_handler(sig, info, ucontext);
    printf("Child pid: %d\n", info->si_pid);
    printf("Child exit status: %d\n", info->si_status);
}

void signal_handler(int sig, siginfo_t* info, void* ucontext) {
    printf("Handle a signal...\n");
}

void set_sigaction(int signo, int flags, void (*action)(int, siginfo_t*, void*)) {
    struct sigaction act;
    act.sa_sigaction = action;
    act.sa_flags = flags;
    sigemptyset(&act.sa_mask);

    sigaction(signo, &act, NULL);
}

int main(int argc, char **argv) {
    printf("\n");

    set_sigaction(SIGUSR1, SA_SIGINFO, signal_info_handler);
    set_sigaction(SIGUSR2, SA_SIGINFO, signal_data_info_handler);
    set_sigaction(SIGCHLD, SA_SIGINFO, signal_child_info_handler);

    raise(SIGUSR1);

    sigval_t signal_value = { 15 };
    sigqueue(getpid(), SIGUSR2, signal_value);

    pid_t pid = fork();
    if (pid == 0) {
        printf("Child process\n");
        exit(1);
    }
    else {
        printf("Create process with pid: %d\n", pid);
    }

    while (wait(NULL) > 0);

    printf("SA_NODEFER\n");
    set_sigaction(SIGUSR1, SA_NODEFER, signal_handler);

    raise(SIGUSR1);

    printf("SA_RESETHAND\n");
    set_sigaction(SIGUSR1, SA_RESETHAND, signal_handler);

    raise(SIGUSR1);

    raise(SIGUSR1);

    return 0;
}