#include "shared_mem.h"
#include "common.h"
#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h> 
#include <unistd.h>
#include <fcntl.h>

#ifdef SYSTEMV

key_t generate_key(const char *name) {
    key_t key = ftok(HOME, name[0]);
    if (key == -1) {
        perror("Failed on calling ftok()");
        return -1;
    }

    return key;
}

int create_shared_mem(const char *name, int size) {
    printf("[Shared memory] Creating a shared memory... ");

    key_t key = generate_key(name);
    if (key == -1) {
        fprintf(stderr, "Failed\n");
        return key;
    }

    int shm_id = shmget(key, size, 0664 | IPC_CREAT | IPC_EXCL);
    if (shm_id == -1) {
        fprintf(stderr, "Failed\n");
        perror("Failed on calling shmget()");
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
        perror("Failed on calling shmget()");
        return -1;
    }

    return shm_id;
}

char* attach_shared_mem(const char *name, int size) {
    printf("[Shared memory] Attaching the shared memory... ");

    int shm_id = open_shared_mem(name);
    if (shm_id == -1) {
        fprintf(stderr, "Failed\n");
        return NULL;
    }

    char *shm = shmat(shm_id, NULL, 0);
    if (shm == (char*) -1) {
        fprintf(stderr, "Failed\n");
        return NULL;
    }
    fprintf(stdout, "Succeeded\n");

    return shm;
}

bool detach_shared_mem(char *shm) {
    if (shmdt(shm) == -1) {
        perror("Failed on calling shmdt()");
        return false;
    }

    return true;
}

bool delete_shared_mem(const char *name) {
    printf("[Shared memory] Deleting the shared memory... ");

    int shm_id = open_shared_mem(name);
    if (shm_id == -1) {
        fprintf(stderr, "Failed\n");
        return false;
    }

    if (shmctl(shm_id, IPC_RMID, NULL) == -1) {
        fprintf(stderr, "Failed\n");
        perror("Failed on calling shmctl()");
        return false;
    }
    fprintf(stdout, "Succeeded\n");

    return true;
}

#endif // SYSTEMV
#ifdef POSIX

int create_shared_mem(const char *name, int size) {
    printf("[Shared memory] Creating a shared memory... ");

    int shm_id = shm_open(name, O_CREAT | O_EXCL | O_RDWR, 0664);
    if (shm_id == -1) {
        fprintf(stderr, "Failed\n");
        perror("Failed on calling shm_open()");
        return -1;
    }

    if (ftruncate(shm_id, size) == -1) {
        fprintf(stderr, "Failed\n");
        perror("Failed on calling ftruncate()");
        return -1;
    }
    fprintf(stdout, "Succeeded\n");

    return shm_id;
}

int open_shared_mem(const char *name) {
    int shm_id = shm_open(name, O_CREAT | O_RDWR, 0);
    if (shm_id == -1) {
        perror("Failed on calling shm_open()");
        return -1;
    }

    return shm_id;
}

char* attach_shared_mem(const char *name, int size) {
    printf("[Shared memory] Attaching the shared memory... ");

    int shm_id = open_shared_mem(name);
    if (shm_id == -1) {
        fprintf(stderr, "Failed\n");
        return NULL;
    }

    char *shm = (char*) mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_id, 0);
    if (shm == (char*) -1) {
        fprintf(stderr, "Failed\n");
        return NULL;
    }
    fprintf(stdout, "Succeeded\n");

    return shm;
}

bool detach_shared_mem(char *shm) {
    if (munmap(NULL, QUEUE_SIZE) == -1) {
        perror("Failed on calling munmap()");
        return false;
    }

    return true;
}

bool delete_shared_mem(const char *name) {
    printf("[Shared memory] Deleting the shared memory... ");

    int shm_id = open_shared_mem(name);
    if (shm_id == -1) {
        fprintf(stderr, "Failed\n");
        return false;
    }

    if (shm_unlink(name) == -1) {
        fprintf(stderr, "Failed\n");
        perror("Failed on calling shm_unlink()");
        return false;
    }
    fprintf(stdout, "Succeeded\n");

    return true;
}

#endif // POSIX