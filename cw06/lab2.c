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
    for (i = 0; i < 5; i++) {
        o1.type = i % 2 + 1;
        o1.content = i;
        msgsnd(queue_id, &i, sizeof(struct package), 0);
    }

    return 0;
}