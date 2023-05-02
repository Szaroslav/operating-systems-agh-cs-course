#include "common.h"
#include "semaphore.h"

#define HAIRDRESSER_EXEC    "build/hairdresser"
#define CLIENT_EXEC         "build/client"

int sem_hairdresser;
int sem_chair;
int sem_queue;

void create_semaphores();

int main(int argc, char **argv) {
    printf("[Hairdresser's] Started\n");

    create_semaphores();

    return 0;
}

void create_semaphores() {
    sem_hairdresser = create_semaphore(HAIRDRESSER_SEM_NAME, HAIRDRESSERS_TOTAL);
    sem_chair = create_semaphore(CHAIR_SEM_NAME, CHAIRS_TOTAL);
    sem_queue = create_semaphore(QUEUE_SEM_NAME, QUEUE_SIZE);
}