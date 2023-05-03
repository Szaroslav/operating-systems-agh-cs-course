#include "common.h"
#include "semaphore.h"
#include "shared_mem.h"
#include "queue.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

semaphore_t sem_hairdresser;
semaphore_t sem_chair;
semaphore_t sem_queue;

void open_semaphores();

int main(int argc, char **argv) {
    setbuf(stdout, NULL);
    srand(time(NULL) + getpid());

    printf("[Client %d] Spawned\n", getpid());

    open_semaphores();
    
    char *queue = attach_shared_mem(QUEUE_NAME, QUEUE_SIZE);
    if (queue == NULL)
        return -1;
    if (strlen(queue) >= QUEUE_SIZE) {
        printf("[Client %d] Queue is full\n", getpid());
        return 0;
    }

    hold(sem_queue);

    char haircut = (char) (rand() % 128);
    queue_push(queue, haircut);

    release(sem_hairdresser);
    release(sem_chair);

    detach_shared_mem(queue);

    return 0;
}

void open_semaphores() {
    sem_hairdresser = open_semaphore(HAIRDRESSER_SEM_NAME);
    sem_chair = open_semaphore(CHAIR_SEM_NAME);
    sem_queue = open_semaphore(QUEUE_SEM_NAME);
}