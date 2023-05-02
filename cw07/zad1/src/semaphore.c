#include "semaphore.h"
#include "common.h"
#include <stdio.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>


int create_semaphore(const char* name, int initial_value) {
    printf("Creating a semaphore... ");

    key_t key = ftok(HOME, name[0]);
    if (key == -1) {
        fprintf(stderr, "Failed\n");
        perror("Failed on calling ftok()\n");
        return -1;
    }

    int sem_id = semget(key, 1, 0664 | IPC_CREAT | IPC_EXCL);
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
    key_t key = ftok(HOME, name[0]);
    if (key == -1) {
        perror("Failed on calling ftok()\n");
        return -1;
    }

    int sem_id = semget(key, 1, IPC_CREAT);
    if (sem_id == -1) {
        perror("Failed on calling semget()\n");
        return -1;
    }

    return sem_id;
}

void release(int sem_id) {
    struct sembuf sem_buf = { .sem_num = 0, .sem_op = 1, .sem_flg = 0 };
    if (semop(sem_id, &sem_buf, 1) == -1) {
        perror("Failed release the semaphore on calling semop()");
        return;
    }
}

void hold(int sem_id) {
    struct sembuf sem_buf = { .sem_num = 0, .sem_op = -1, .sem_flg = 0 };
    if (semop(sem_id, &sem_buf, 1) == -1) {
        perror("Failed hold the semaphore on calling semop()");
        return;
    }
}

bool unlink_semaphore(const char *name) {
    return true;
}

bool delete_semaphore(const char *name) {
    printf("Deleting the semephore... ");

    if (!unlink_semaphore(name))
        return false;

    int sem_id = open_semaphore(name);
    if (sem_id == -1)
        return false;

    if (semctl(sem_id, 0, IPC_RMID) == -1) {
        fprintf(stderr, "Failed\n");
        perror("Failed on calling semctl()");
        return false;
    }
    fprintf(stdout, "Succeeded\n");

    return true;
}