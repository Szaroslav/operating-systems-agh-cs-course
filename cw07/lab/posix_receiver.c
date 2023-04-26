#include <stdio.h>
#include <string.h>
#include <mqueue.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>

#define BLOCK_SIZE 1024

int main(int argc, char **argv) {
    int fd = shm_open("/name", O_CREAT | O_RDWR, 0644);
    ftruncate(fd, BLOCK_SIZE);
    char *ptr = (char *) mmap(NULL, BLOCK_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    printf("Receiver: %s\n", ptr);

    munmap(ptr, BLOCK_SIZE);
    shm_unlink("/name");

    return 0;
}