#include "common.h"
#include "semaphore.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

int sem_hairdresser;
int sem_chair;
int sem_queue;

void open_semaphores();

int main(int argc, char **argv) {
    printf("[Hairdresser%d] Spawned\n", getpid());

    open_semaphores();

    while (true) {
        hold(sem_hairdresser);
        printf("[Hairdresser%d] Cutting a client head's hair... ", getpid());

        usleep(2000);

        release(sem_hairdresser);
        printf("Succeeded\n");
    }

    return 0;
}

void open_semaphores() {
    sem_hairdresser = open_semaphore(HAIRDRESSER_SEM_NAME);
    sem_chair = open_semaphore(CHAIR_SEM_NAME);
    sem_queue = open_semaphore(QUEUE_SEM_NAME);
}