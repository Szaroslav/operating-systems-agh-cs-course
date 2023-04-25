#include "common.h"
#include <stdio.h>
#include <string.h>
#include <mqueue.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

mqd_t sqd;
mqd_t client_queues[MAX_CLIENTS_NUMBER] = { 0 };
uint current_queue_size = 0;
Message msg;
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
    mt_to_string(msg.message_type, mt);

    char buffer[BUFSIZ];
    buffer[0] = '\0';
    int l = snprintf(buffer, BUFSIZ, "%s\tclient id: %d\t%s\n", curr_time, msg.client_id, mt);
    write(fd, buffer, l);
}

void on_init() {
    printf("\n[Server] Receive INIT message\n");
    printf("[Server] Client queue name: %s\n", msg.client_queue_name);

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

    client_queues[cid] = mq_open(msg.client_queue_name, O_WRONLY | O_CREAT | O_EXCL);;
    if (client_queues[cid] == -1) {
        printf("Failed\n");
        return;
    }
    current_queue_size++;

    printf("Succeed\n");

    printf("[Server] Client ID: %d\n", cid);
    printf("[Server] Client queue ID: %d\n", client_queues[cid]);

    printf("[Server] Responding to client with its ID... ");
    msg.message_type = MT_INIT; msg.client_id = cid;
    if (mq_send(client_queues[cid], (char *) &msg, MESSAGE_SIZE, DEFAULT_PRIORITY) != 0) {
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
    msg.message_type = MT_LIST; strcpy(msg.message, buffer);
    if (mq_send(client_queues[cid], (char *) &msg, MESSAGE_SIZE, DEFAULT_PRIORITY) == -1) {
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

    mq_send(client_queues[cid], (char *) &msg, MESSAGE_SIZE, DEFAULT_PRIORITY);
}

void on_send_to_all() {
    printf("\n[Server] Receive 2ALL message\n");
    printf("[Server] Client ID: %d\n", msg.client_id);

    int cid = msg.client_id;
    Message new_msg = { .message_type = MT_MESSAGE, .client_id = msg.client_id };
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

    Message new_msg = { .message_type = MT_MESSAGE, .client_id = msg.client_id };
    strcpy(new_msg.message, msg.message);

    send_to_one(msg.to_client_id, &new_msg);
}

void on_sigint(int signum) {
    exit(1);
}

void onexit() {
    if (fd > 0)
        close(fd);

    msg.message_type = MT_STOP;
    int cid = msg.client_id;
    for (int id = 0; id < MAX_CLIENTS_NUMBER; id++) {
        if (client_queues[id] > 0) {
            mq_send(client_queues[cid], (char *) &msg, MESSAGE_SIZE, MT_STOP);
            mq_receive(sqd, (char *) &msg, MESSAGE_SIZE, NULL);
            on_stop();
        }
    }
    
    printf("[Server] Deleting queue... ");
    // if (msgctl(sqd, IPC_RMID, &qds) == -1) {
    //     printf("Failed\n");
    //     return;
    // }
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

    struct mq_attr smq_attr = {
        .mq_flags = O_NONBLOCK,
        .mq_maxmsg = 32,
        .mq_msgsize = MESSAGE_SIZE,
        .mq_curmsgs = 0
    };

    sqd = mq_open(SERVER_NAME, O_WRONLY | O_CREAT, 0664, &smq_attr);

    if (sqd == -1) {
        printf("Failed\n");
        return -1;
    }
    printf("Succeed\n");

    while (1) {
        if (mq_receive(sqd, (char *) &msg, MESSAGE_SIZE, NULL) >= 0) {
            save_output_to_file();
            
            switch (msg.message_type) {
                case MT_STOP:
                    on_stop();
                    break;
                case MT_INIT:
                    on_init();
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
        // else if (msgrcv(sqd, &msg, MESSAGE_SIZE, MT_STOP, IPC_NOWAIT | MSG_EXCEPT) >= 0) {
            
        // }
    }

    return 0;
}