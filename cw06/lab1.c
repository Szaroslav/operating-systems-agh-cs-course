#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    int i;
    key_t key = ftok("./file1", 'p');
    
    printf("Key: %d\n", key);

    int queue_id = msgget(key, IPC_CREAT | 0600);
    for (i = 0; i < 5; i++) msgsnd(queue_id, &i, sizeof(int), 0);

    return 0;
}