#include "common.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

int sqid;
int client_queues[MAX_CLIENTS_NUMBER] = { 0 };
uint current_queue_size = 0;
Message msg;
struct msqid_ds qds;
int fd;


int get_client_id() {
    if (current_queue_size >= MAX_CLIENTS_NUMBER)
        return -1;
    
    for (int i = 0; i < MAX_CLIENTS_NUMBER; i++)
        if (client_queues[i] == 0)
            return i;

    return -1;
}

void mt_to_string(MessageType mt, char *buf) {
    switch (mt) {
        case MT_STOP:
            strcpy(buf, "STOP");
            break;
        case MT_INIT:
            strcpy(buf, "INIT");
            break;
        case MT_LIST:
            strcpy(buf, "LIST");
            break;
        case MT_SEND_ALL:
            strcpy(buf, "2ALL");
            break;
        case MT_SEND_ONE:
            strcpy(buf, "2ONE");
            break;
        default:
            strcpy(buf, "");
    }
}

void save_output_to_file() {
    char curr_time[64];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(curr_time, 64, "%d-%02d-%02d %02d:%02d:%02d",
        tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec
    );

    char mt[64];
    mt_to_string(msg.mtype, mt);

    char buffer[BUFSIZ];
    buffer[0] = '\0';
    int l = snprintf(buffer, BUFSIZ, "%s\tclient id: %d\t%s\n", curr_time, msg.client_id, mt);
    write(fd, buffer, l);
}

void on_init(key_t key) {
    printf("\n[Server] Receive INIT message\n");
    printf("[Server] Client queue key: %d\n", key);

    printf("[Server] Accessing a client queue from the key... ");

    if (current_queue_size >= MAX_CLIENTS_NUMBER) {
        printf("Failed\n");
        return;
    }

    int cid = get_client_id();
    if (cid == -1) {
        printf("Failed\n");
        return;
    }

    client_queues[cid] = msgget(key, IPC_CREAT);
    if (client_queues[cid] == -1) {
        printf("Failed\n");
        return;
    }
    current_queue_size++;

    printf("Succeed\n");

    printf("[Server] Client ID: %d\n", cid);
    printf("[Server] Client queue ID: %d\n", client_queues[cid]);

    printf("[Server] Responding to client with its ID... ");
    msg.mtype = MT_INIT; msg.client_id = cid;
    if (msgsnd(client_queues[cid], &msg, MESSAGE_SIZE, 0) != 0) {
        printf("Failed\n");
        return;
    }
    printf("Succeed\n");
}

void on_stop() {
    printf("\n[Server] Receive STOP message\n");
    printf("[Server] Client ID: %d\n", msg.client_id);

    printf("[Server] Removing the client queue... ");

    if (client_queues[msg.client_id] == 0) {
        printf("Failed\n");
        return;
    }

    client_queues[msg.client_id] = 0;
    current_queue_size--;
    printf("Succeed\n");
}

void on_list() {
    printf("\n[Server] Receive LIST message\n");
    printf("[Server] Client ID: %d\n", msg.client_id);

    int cid = msg.client_id;

    char buffer[MAX_MESSAGE_SIZE];
    buffer[0] = '\0';
    for (int id = 0; id < MAX_CLIENTS_NUMBER; id++) {
        if (client_queues[id] == 0)
            continue;
        
        char id_str[8];
        sprintf(id_str, "%d", id);
        strcat(buffer, id_str);
        if (id == cid)
            strcat(buffer, " (you)");
        strcat(buffer, "\n");
    }
    
    printf("[Server] Responding to client with list of all clients... ");
    msg.mtype = MT_LIST; strcpy(msg.message, buffer);
    if (msgsnd(client_queues[cid], &msg, MESSAGE_SIZE, 0) == -1) {
        printf("Failed\n");
        return;
    }
    printf("Succeed\n");
}

void send_to_one(const int cid, Message *msg) {
    if (cid < 0 || cid >= MAX_CLIENTS_NUMBER || client_queues[cid] == 0) {
        printf("[Server] Sending a message to %d is disallowed\n", cid);
        return;
    }

    msgsnd(client_queues[cid], msg, MESSAGE_SIZE, 0);
}

void on_send_to_all() {
    printf("\n[Server] Receive 2ALL message\n");
    printf("[Server] Client ID: %d\n", msg.client_id);

    int cid = msg.client_id;
    Message new_msg = { .mtype = MT_MESSAGE, .client_id = msg.client_id };
    strcpy(new_msg.message, msg.message);

    for (int id = 0; id < MAX_CLIENTS_NUMBER; id++) {
        if (client_queues[id] == 0 || id == cid)
            continue;
        
        send_to_one(id, &new_msg);
    }
}

void on_send_to_one() {
    printf("\n[Server] Receive 2ONE message\n");
    printf("[Server] Client ID: %d\n", msg.client_id);

    Message new_msg = { .mtype = MT_MESSAGE, .client_id = msg.client_id };
    strcpy(new_msg.message, msg.message);

    send_to_one(msg.to_client_id, &new_msg);
}

void on_sigint(int signum) {
    exit(1);
}

void onexit() {
    if (fd > 0)
        close(fd);

    msg.mtype = MT_STOP;
    for (int id = 0; id < MAX_CLIENTS_NUMBER; id++) {
        if (client_queues[id] > 0) {
            msgsnd(client_queues[id], &msg, MESSAGE_SIZE, 0);
            msgrcv(sqid, &msg, MESSAGE_SIZE, MT_STOP, 0);
            on_stop();
        }
    }
    
    printf("[Server] Deleting queue... ");
    if (msgctl(sqid, IPC_RMID, &qds) == -1) {
        printf("Failed\n");
        return;
    }
    printf("Succeed\n");

    printf("\n[Server] Stopped\n");
}

int main(int argc, char **argv) {
    printf("[Server] Started\n");

    struct sigaction action;
    action.sa_handler = on_sigint;
    sigaction(SIGINT, &action, NULL);

    atexit(onexit);

    printf("[Server] Opening output file... ");
    fd = open("results.txt", O_CREAT | O_WRONLY, 0664);
    if (fd == -1) {
        printf("Failed\n");
        return -1;
    }
    printf("Succeed\n");

    printf("[Server] Creating the server queue... ");
    key_t key = ftok(HOME, SERVER_ID);
    sqid = msgget(key, IPC_CREAT | 0666);

    if (sqid == -1) {
        printf("Failed\n");
        return -1;
    }
    printf("Succeed\n");

    while (1) {
        // printf("?\n");
        // printf("%ld\n", msgrcv(sqid, &msg, MESSAGE_SIZE, MT_STOP, IPC_NOWAIT));
        if (msgrcv(sqid, &msg, MESSAGE_SIZE, MT_STOP, IPC_NOWAIT) >= 0) {
            save_output_to_file();
            on_stop();
        }
        else if (msgrcv(sqid, &msg, MESSAGE_SIZE, MT_STOP, IPC_NOWAIT | MSG_EXCEPT) >= 0) {
            // printf("%ld\n", msg.mtype);
            save_output_to_file();
            switch (msg.mtype) {
                case MT_INIT:
                    on_init(msg.client_queue_key);
                    break;
                case MT_LIST:
                    on_list();
                    break;
                case MT_SEND_ALL:
                    on_send_to_all();
                    break;
                case MT_SEND_ONE:
                    on_send_to_one();
                    break;
            }
        }
    }

    return 0;
}