#include "shared_mem.h"
#include "common.h"
#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>


key_t generate_key(const char *name) {
    key_t key = ftok(HOME, name[0]);
    if (key == -1) {
        fprintf(stderr, "Failed\n");
        perror("Failed on calling ftok()\n");
        return -1;
    }

    return key;
}

int create_shared_mem(const char *name, int size) {
    printf("[Shared memory] Creating a shared memory... ");

    key_t key = generate_key(name);
    if (key == -1)
        return key;

    int shm_id = shmget(key, size, 0664 | IPC_CREAT | IPC_EXCL);
    if (shm_id == -1) {
        fprintf(stderr, "Failed\n");
        perror("Failed on calling shmget()\n");
        return -1;
    }
    fprintf(stdout, "Succeeded\n");

    return shm_id;
}

int open_shared_mem(const char *name) {
    key_t key = generate_key(name);
    if (key == -1)
        return key;
    
    int shm_id = shmget(key, 0, IPC_CREAT);
    if (shm_id == -1) {
        perror("Failed on calling shmget()\n");
        return -1;
    }

    return shm_id;
}

char* attach_shared_mem(const char *name) {
    printf("[Shared memory] Attaching the shared memory... ");

    int shm_id = open_shared_mem(name);
    if (shm_id == -1)
        return NULL;

    char *shm = shmat(shm_id, NULL, 0);
    if (shm == (char*) -1) {
        fprintf(stderr, "Failed\n");
        return NULL;
    }
    fprintf(stdout, "Succeeded\n");

    return shm;
}

bool detach_shared_mem(char *shm) {
    printf("[Shared memory] Detaching the shared memory... ");

    if (shmdt(shm) == -1) {
        fprintf(stderr, "Failed\n");
        perror("Failed on calling shmdt()\n");
        return false;
    }
    fprintf(stdout, "Succeeded\n");

    return true;
}

bool delete_shared_mem(const char *name) {
    printf("[Shared memory] Deleting the shared memory... ");

    int shm_id = open_shared_mem(name);
    if (shm_id == -1)
        return false;

    if (shmctl(shm_id, IPC_RMID, NULL) == -1) {
        fprintf(stderr, "Failed\n");
        perror("Failed on calling shmctl()\n");
        return false;
    }
    fprintf(stdout, "Succeeded\n");

    return true;
}