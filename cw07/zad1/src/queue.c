#include "queue.h"
#include "common.h"
#include <stdio.h>
#include <string.h>


char queue_pop(char *queue) {
    if(queue_empty(queue)) {
        fprintf(stderr, "[Error] Failed to pop from queue, the queue is empty\n");
        return '\0';
    }

    char byte = queue[0];
    memmove(queue, queue + 1, strlen(queue) + 1);

    return byte;
}

void queue_push(char *queue, char byte) {
    if(queue_full(queue)) {
        fprintf(stderr, "[Error] Failed to push to queue, the queue is full\n");
        return;
    }

    int size = strlen(queue);
    queue[size] = byte;
    queue[size + 1] = '\0';
}

bool queue_full(char *queue) {
    return strlen(queue) >= QUEUE_SIZE;
}

bool queue_empty(char *queue) {
    return strlen(queue) == 0;
}