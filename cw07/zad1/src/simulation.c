#include "common.h"
#include "semaphore.h"
#include "shared_mem.h"
#include <stdio.h>

#define HAIRDRESSER_EXEC    "build/hairdresser"
#define CLIENT_EXEC         "build/client"

int sem_hairdresser;
int sem_chair;
int sem_queue;

void create_semaphores();
void delete_semaphores();

int main(int argc, char **argv) {
    setbuf(stdout, NULL);

    printf("Simulation started\n");

    create_semaphores();

    create_shared_mem(QUEUE_NAME, QUEUE_SIZE + 1);
    char *queue = attach_shared_mem(QUEUE_NAME);
    if (queue == NULL)
        return -1;

    detach_shared_mem(queue);
    delete_shared_mem(QUEUE_NAME);

    delete_semaphores();

    return 0;
}

void create_semaphores() {
    sem_hairdresser = create_semaphore(HAIRDRESSER_SEM_NAME, HAIRDRESSERS_TOTAL);
    sem_chair = create_semaphore(CHAIR_SEM_NAME, CHAIRS_TOTAL);
    sem_queue = create_semaphore(QUEUE_SEM_NAME, QUEUE_SIZE);
}

void delete_semaphores() {
    delete_semaphore(HAIRDRESSER_SEM_NAME);
    delete_semaphore(CHAIR_SEM_NAME);
    delete_semaphore(QUEUE_SEM_NAME);
}
