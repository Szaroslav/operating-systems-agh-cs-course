#include "cli.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

void handle_signal(int signum) {
    printf("Hello\n");
}

void handle(int signum, siginfo_t *si, void *p3) {
    printf("Signal v1: %d %d, war: %d\n", si->si_pid, si->si_uid, si->si_value);
}

int main(int argc, char **argv) {
    if (cli_verify_args(argc, argv) != 0) {
        return -1;
    }

    const char *sig_types[] = {
        "ignore",
        "handler",
        "mask",
        "pending"
    };

    // if (fork() == 0) {
    //     sigset_t newmask, oldmask, set;

    //     if (strcmp(argv[0], sig_types[0])) {
    //         signal(SIGUSR1, SIG_IGN);
    //     }
    //     else if (strcmp(argv[0], sig_types[1])) {
    //         signal(SIGUSR1, handle_signal);
    //     }
    //     else if (strcmp(argv[0], sig_types[2])) {   
    //         sigemptyset(&newmask);
    //         sigaddset(&newmask, SIGUSR1);
    //         sigprocmask(SIG_BLOCK, &newmask, &oldmask);
    //     }
        // else if (strcmp(argv[0], sig_types[3])) {
            
        // }   


        union sigval war;
        int pid;

        pid = atoi(tab[1]);
        // sigemptyset(&set);

        war.sival_int = 123;
        sigqueue(pid, SIGUSR1, war);
        // sigsuspend(&set);
        

        sigset_t set;
        struct sigaction act;
        int i;

        act.sa_sigaction = handle1;
        sigemptyset(&act.sa_mask);
        act.sa_flags = SA_SIGINFO();
        sigaction(SIGUSR1, &act, NULL); 
        
        raise(SIGUSR1);

        // if (strcmp(argv[0], sig_types[2])) {
        //     sigpending(&set);
        //     if (sigismember(&set, SIGUSR1) == 1)
        //         printf("SIGUSR1 waits for unlocking (1)\n");
        // }
    
        printf("Hello\n");
    }
}