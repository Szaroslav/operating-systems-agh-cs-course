#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct package {
    long type;
    int content;
};

int main() {
    int i;
    struct package o1;
    key_t key = ftok("./file1", 'p');
    
    printf("Key: %d\n", key);

    int queue_id = msgget(key, IPC_CREAT | 0600);
    
    while (1) {
        if (msgrcv(queue_id, &o1, sizeof(struct package), 1, IPC_NOWAIT) < 0)
            break;
        printf("Received: %d\n", o1.content);
    }

    while (1) {
        if (msgrcv(queue_id, &o1, sizeof(struct package), 2, IPC_NOWAIT) < 0)
            break;
        printf("Received: %d\n", o1.content);
    }

    return 0;
}