#include "common.h"
#include "semaphore.h"
#include "shared_mem.h"
#include "queue.h"
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define HAIRCUT_TIME_MSEC 250000

semaphore_t sem_hairdresser;
semaphore_t sem_chair;
semaphore_t sem_queue;

void open_semaphores();

int main(int argc, char **argv) {
    setbuf(stdout, NULL);
    srand(time(NULL));

    printf("[Hairdresser %d] Spawned\n", getpid());

    open_semaphores();
    
    char *queue = attach_shared_mem(QUEUE_NAME, QUEUE_SIZE);
    if (queue == NULL)
        return -1;

    while (true) {
        hold(sem_hairdresser);

        char haircut = queue_pop(queue);

        printf("[Hairdresser %d] Estimated processing time for haircut no. %hhd is %f s\n",
            getpid(), haircut, haircut * HAIRCUT_TIME_MSEC / 1000000.0
        );
        printf("[Hairdresser %d] Processing haircut no. %hhd... ", getpid(), haircut);
        usleep(haircut * HAIRCUT_TIME_MSEC);
        printf("Finished\n");

        release(sem_chair);
        release(sem_queue);

        if (queue_empty(queue)) {
            // Wait for potential clients spawn
            sleep(1);
            if (queue_empty(queue))
                break;
        }
    }

    printf("[Hairdresser %d] Job finished, going to sleep\n", getpid());

    detach_shared_mem(queue);

    return 0;
}

void open_semaphores() {
    sem_hairdresser = open_semaphore(HAIRDRESSER_SEM_NAME);
    sem_chair = open_semaphore(CHAIR_SEM_NAME);
    sem_queue = open_semaphore(QUEUE_SEM_NAME);
}