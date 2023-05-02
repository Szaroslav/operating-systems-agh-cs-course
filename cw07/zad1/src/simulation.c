#include "common.h"
#include "semaphore.h"
#include "shared_mem.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int sem_hairdresser;
int sem_chair;
int sem_queue;

void create_semaphores();
void delete_semaphores();

int main(int argc, char **argv) {
    setbuf(stdout, NULL);

    printf("Simulation has been started\n\n");

    create_semaphores();

    create_shared_mem(QUEUE_NAME, QUEUE_SIZE + 1);
    char *queue = attach_shared_mem(QUEUE_NAME);
    if (queue == NULL)
        return -1;

    for (int i = 0; i < HAIRDRESSERS_TOTAL; i++) {
        if (fork() == 0) {
            execl(HAIRDRESSER_PATH, HAIRDRESSER_EXEC, (char *) NULL);
        }
    }

    for (int i = 0; i < CLIENTS_TOTAL; i++) {
        if (fork() == 0) {
            execl(CLIENT_PATH, CLIENT_EXEC, (char *) NULL);
        }
    }

    while(wait(NULL) > 0);

    detach_shared_mem(queue);
    delete_shared_mem(QUEUE_NAME);

    delete_semaphores();

    printf("\nSimulation has been finished\n");

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
