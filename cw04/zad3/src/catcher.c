#include "mode.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

#define BUFFER_SIZE 128

enum Mode mode;
int executed = 1;
int request_count = 0;
int pid;

void handle_signal(int signo, siginfo_t* info, void* context) {
    pid = info->si_pid;
    int value = info->si_status;

    if (value >= 1 && value <= 5) {
        request_count += 1;
        mode = value;
        executed = 0;
    } else {
        fprintf(stderr, "Invalid status [%d]\n", value);
    }

    kill(pid, SIGUSR1);
}

void set_sigaction() {
    struct sigaction act;
    act.sa_sigaction = handle_signal;
    act.sa_flags = SA_SIGINFO;
    sigemptyset(&act.sa_mask);

    sigaction(SIGUSR1, &act, NULL);
}

void print_current_time() {
    time_t raw_time;
    struct tm* time_info;
    time(&raw_time);
    time_info = localtime(&raw_time);
    printf("Current time: %s", asctime(time_info));
}

void print_numbers(int from, int to) {
    for (int i = from; i <= to; i++)
        printf("%d ", i);
    printf("\n");
}

void print_requests() {
    printf("Number of all requests: %d\n", request_count);
}

void print_current_time_interval(double delta) {
    double acc = 1.0;

    acc += delta;
    if (acc >= 1.0) {
        print_current_time();
        acc = 0.0;
    }
}

void close_p() {
    printf("Exiting, goodbye\n");
    fflush(stdout);
    exit(0);
}

int main(int argc, char **argv) {
    printf("Catcher (PID: %d)\n", getpid());
    printf("Waiting for signals...\n\n");

    set_sigaction();

    clock_t start = clock();
    clock_t end = clock();

    while (1) {
        if (executed)
            continue;
        
        const double delta = (end - start) / (double) CLOCKS_PER_SEC;
        start = clock();

        switch (mode) {
            case M_PNUMS:
                print_numbers(1, 100);
                break;
            case M_STIME:
                print_current_time();
                break;
            case M_PCHANGES:
                print_requests();
                break;
            case M_ITIME:
                print_current_time_interval(delta);
                break;
            case M_EXIT:
                close_p();
                break;
        }

        if (mode != M_ITIME) {
            executed = 1;
        }

        end = clock();
    }
    
    return 0;
}