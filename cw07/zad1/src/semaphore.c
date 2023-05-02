#include "semaphore.h"
#include "common.h"
#include <stdio.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <fcntl.h>

char person_buf[128];

int create_semaphore(const char* name, int initial_value) {
    printf("[%s] Creating a semaphore... \n", person_buf);

    key_t key = ftok(HOME, name[0]);
    if (key == -1) {
        fprintf(stderr, "Failed\n");
        perror("Failed on calling ftok()\n");
        return -1;
    }

    int sem_id = semget(key, 1, 0664 | O_CREAT);
    if (sem_id == -1) {
        fprintf(stderr, "Failed\n");
        perror("Failed on calling semget()\n");
        return -1;
    }

    if (semctl(sem_id, 0, SETVAL, initial_value) == -1) {
        fprintf(stderr, "Failed\n");
        perror("Failed on calling semctl()\n");
        return -1;
    }

    fprintf(stdout, "Succeeded\n");
    return sem_id;
}

int open_semaphore(const char* name) {
    printf("[%s] Opening the semaphore... \n", person_buf);

    key_t key = ftok(HOME, name[0]);
    if (key == -1) {
        fprintf(stderr, "Failed\n");
        perror("Failed on calling ftok()\n");
        return -1;
    }

    int sem_id = semget(key, 1, O_CREAT | O_EXCL);
    if (sem_id == -1) {
        fprintf(stderr, "Failed\n");
        perror("Failed on calling semget()\n");
        return -1;
    }

    fprintf(stdout, "Succeeded\n");
    return sem_id;
}

void release(int sem_id) {
    printf("Releasing the semephore... ");

    struct sembuf sem_buf = { .sem_num = 0, .sem_op = 1, .sem_flg = 0 };
    if (semop(sem_id, &sem_buf, 1) == -1) {
        fprintf(stderr, "Failed\n");
        perror("Failed on calling semop()");
        return;
    }
    fprintf(stdout, "Succeeded\n");
}

void hold(int sem_id) {
    printf("Holding the semephore... ");

    struct sembuf sem_buf = { .sem_num = 0, .sem_op = -1, .sem_flg = 0 };
    if (semop(sem_id, &sem_buf, 1) == -1) {
        fprintf(stderr, "Failed\n");
        perror("Failed on calling semop()");
        return;
    }
    fprintf(stdout, "Succeeded\n");
}

void smp_close(const char *name) {
    printf("Closing the semephore... ");

    int sem_id = open_semaphore(name);
    if (sem_id == -1)
        return;
    
    if (semctl(sem_id, 0, IPC_RMID) == -1) {
        fprintf(stderr, "Failed\n");
        perror("Failed on calling semctl()");
        return;
    }
    fprintf(stdout, "Succeeded\n");
}