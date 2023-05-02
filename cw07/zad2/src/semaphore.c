#include "semaphore.h"
#include "common.h"
#include <stdio.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <semaphore.h>
#include <fcntl.h>
#include <errno.h>

#ifdef SYSTEMV

semaphore_t create_semaphore(const char* name, int initial_value) {
    printf("Creating a semaphore... ");

    key_t key = ftok(HOME, name[0]);
    if (key == -1) {
        fprintf(stderr, "Failed\n");
        perror("Failed on calling ftok()");
        return -1;
    }

    semaphore_t sem_id = semget(key, 1, 0664 | IPC_CREAT | IPC_EXCL);
    if (sem_id == -1) {
        fprintf(stderr, "Failed\n");
        perror("Failed on calling semget()");
        return -1;
    }

    if (semctl(sem_id, 0, SETVAL, initial_value) == -1) {
        fprintf(stderr, "Failed\n");
        perror("Failed on calling semctl()");
        return -1;
    }

    fprintf(stdout, "Succeeded\n");
    return sem_id;
}

semaphore_t open_semaphore(const char* name) {
    key_t key = ftok(HOME, name[0]);
    if (key == -1) {
        perror("Failed on calling ftok()");
        return -1;
    }

    semaphore_t sem_id = semget(key, 1, IPC_CREAT);
    if (sem_id == -1) {
        perror("Failed on calling semget()");
        return -1;
    }

    return sem_id;
}

void release(semaphore_t sem_id) {
    struct sembuf sem_buf = { .sem_num = 0, .sem_op = 1, .sem_flg = 0 };
    if (semop(sem_id, &sem_buf, 1) == -1) {
        perror("Failed release the semaphore on calling semop()");
        return;
    }
}

void hold(semaphore_t sem_id) {
    struct sembuf sem_buf = { .sem_num = 0, .sem_op = -1, .sem_flg = 0 };
    if (semop(sem_id, &sem_buf, 1) == -1) {
        perror("Failed hold the semaphore on calling semop()");
        return;
    }
}

bool close_semaphore(semaphore_t sem_id) {
    return true;
}

bool delete_semaphore(const char *name) {
    printf("Deleting the semephore...\n");

    int sem_id = open_semaphore(name);
    if (sem_id == -1)
        return false;

    if (!close_semaphore(sem_id))
        return false;

    if (semctl(sem_id, 0, IPC_RMID) == -1) {
        perror("Failed on calling semctl()");
        return false;
    }

    return true;
}

#endif // SYSTEMV
#ifdef POSIX

semaphore_t create_semaphore(const char* name, int initial_value) {
    printf("Creating a semaphore... ");

    semaphore_t sem_id = sem_open(name, O_CREAT | O_EXCL, 0664, initial_value);
    if (sem_id == SEM_FAILED) {
        fprintf(stderr, "Failed\n");
        perror("Failed on calling sem_open()");
        return SEM_FAILED;
    }

    fprintf(stdout, "Succeeded\n");
    return sem_id;
}

semaphore_t open_semaphore(const char* name) {
    semaphore_t sem_id = sem_open(name, O_CREAT);
    if (sem_id == SEM_FAILED) {
        fprintf(stderr, "Failed\n");
        perror("Failed on calling sem_open()");
        return SEM_FAILED;
    }

    fprintf(stdout, "Succeeded\n");
    return sem_id;
}

void release(semaphore_t sem_id) {
    if (sem_post(sem_id) == -1) {
        perror("Failed release the semaphore on calling sem_post()");
        return;
    }
}

void hold(semaphore_t sem_id) {
    if (sem_wait(sem_id) == -1) {
        perror("Failed hold the semaphore on calling sem_wait()");
        return;
    }
}

bool close_semaphore(semaphore_t sem_id) {
    if (sem_close(sem_id) == -1) {
        perror("Failed close the semaphore on calling sem_close()");
        return false;
    }

    return true;
}

bool delete_semaphore(const char *name) {
    printf("Deleting the semephore...\n");

    semaphore_t sem_id = open_semaphore(name);
    if (sem_id == SEM_FAILED)
        return false;

    if (!close_semaphore(sem_id))
        return false;

    if (sem_unlink(name) == -1) {
        perror("Failed on calling sem_unlink()");
        return false;
    }

    return true;
}

#endif // POSIX