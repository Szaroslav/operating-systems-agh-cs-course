#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <signal.h>

int cid;
int cqid;
int sqid;
key_t key;
struct msqid_ds qds;
char buffer[BUFSIZ];
pid_t receiver_pid;


MessageType to_message_type(const char *str) {
    if (strcmp(str, "LIST") == 0)
        return MT_LIST;
    if (strcmp(str, "2ALL") == 0)
        return MT_SEND_ALL;
    if (strcmp(str, "2ONE") == 0)
        return MT_SEND_ONE;
    if (strcmp(str, "STOP") == 0)
        return MT_STOP;

    printf("[Client] Wrong command (allowed: [LIST|2ALL|2ONE|STOP]). Exiting...\n");
    exit(-1);
}

void init(Message *msg, key_t key) {
    printf("\n[Client] Sending INIT message to the server... ");
    msg->mtype = MT_INIT; msg->client_queue_key = key;

    if (msgsnd(sqid, msg, MESSAGE_SIZE, 0) == -1) {
        printf("Failed\n");
        return;
    }
    printf("Succeed\n");

    printf("[Client] Waiting for response from the server... ");
    while (msgrcv(cqid, msg, MESSAGE_SIZE, MT_INIT, 0) < 0);
    printf("Succeed\n");
    cid = msg->client_id;
    printf("[Client] Client ID: %d\n", cid);
}

// void on_init_response(Message *msg) {
//     printf("[Client] Receive response from the server\n");
//     cid = msg->client_id;
//     printf("[Client] Client ID: %d\n", cid);
// }

void stop(Message *msg, bool send_msg) {
    if (send_msg) {
        printf("\n[Client] Sending STOP message to the server... ");
        msg->mtype = MT_STOP; msg->client_id = cid;

        if (msgsnd(sqid, msg, MESSAGE_SIZE, 0) == -1) {
            printf("Failed\n");
        }
        else {
            printf("Succeed\n");
        }
    }

    printf("[Client] Deleting queue... ");
    if (msgctl(cqid, IPC_RMID, &qds) == -1) {
        printf("Failed\n");
        return;
    }
    printf("Succeed\n");
    
    exit(1);
}

void list(Message *msg) {
    printf("\n[Client] Sending LIST message to the server... ");
    msg->mtype = MT_LIST; msg->client_id = cid;

    if (msgsnd(sqid, msg, MESSAGE_SIZE, 0) == -1) {
        printf("Failed\n");
        return;
    }
    printf("Succeed\n");

    // printf("[Client] Waiting for response from the server... ");
    // while (msgrcv(cqid, msg, MESSAGE_SIZE, MT_RESPONSE, 0) == -1);
    // printf("Succeed\n");

    // printf("%s", msg->message);
}

void on_list_response(Message *msg) {
    printf("\n[Client] Receive response from the server\n");
    printf("%s", msg->message);
    cid = msg->client_id;
    printf("[Client] Client ID: %d\n", cid);
}

void send_to_all(Message *msg) {
    printf("\n[Client] Sending 2ALL message to the server... ");
    msg->mtype = MT_SEND_ALL; msg->client_id = cid;

    if (msgsnd(sqid, msg, MESSAGE_SIZE, 0) == -1) {
        printf("Failed\n");
        return;
    }
    printf("Succeed\n");
}

void send_to_one(Message *msg) {
    printf("\n[Client] Sending 2ONE message to the server... ");
    msg->mtype = MT_SEND_ONE; msg->client_id = cid;

    if (msgsnd(sqid, msg, MESSAGE_SIZE, 0) == -1) {
        printf("Failed\n");
        return;
    }
    printf("Succeed\n");
}

void on_message(Message *msg) {
    printf("\n[Client] Receive message from the server\n");
    printf("[Client %d] %s\n", msg->client_id, msg->message);
    fflush(stdout);
}

void on_sigint(int signum) {
    Message msg;
    stop(&msg, true);
}

void onexit() {
    if (receiver_pid > 0)
        kill(receiver_pid, SIGKILL);
    else if (getppid() > 0)
        kill(getppid(), SIGINT);
    
    printf("[Client] Stopped\n");
}

int main(int argc, char **argv) {
    printf("[Client] Started\n");

    atexit(onexit);
    srand(time(NULL));

    printf("[Client] Creating a client queue... ");
    key = ftok(HOME, rand() % 254 + 2);
    while ((cqid = msgget(key, IPC_CREAT | IPC_EXCL | 0666)) <= 0)
        key = ftok(HOME, rand() % 254 + 2);;

    if (cqid == -1) {
        printf("Failed\n");
        return -1;
    }

    printf("Succeed\n");

    printf("[Client] Client queue key: %d\n", key);
    printf("[Client] Client queue ID: %d\n", cqid);

    printf("[Client] Accessing the server queue... ");
    key_t skey = ftok(HOME, SERVER_ID);
    sqid = msgget(skey, IPC_CREAT | 0666);

    if (sqid == -1) {
        printf("Failed\n");
        return -1;
    }
    printf("Succeed\n");

    Message msg;
    init(&msg, key);

    receiver_pid = fork();
    if (receiver_pid == 0) {
        Message msg;
        while (true) {
            if (msgrcv(cqid, &msg, MESSAGE_SIZE, 0, 0) >= 0) {
                // printf("!%ld\n", msg.mtype);
                switch (msg.mtype) {
                    case MT_STOP:
                        kill(getppid(), SIGINT);
                        break;
                    case MT_LIST:
                        on_list_response(&msg);
                        break;
                    case MT_MESSAGE:
                        on_message(&msg);
                        break;
                }
            }
        }
    }
    else {
        struct sigaction action;
        action.sa_handler = on_sigint;
        sigaction(SIGINT, &action, NULL);

        while (fgets(buffer, BUFSIZ, stdin) != NULL) {
            char command[BUFSIZ];
            int client_id;
            char message[MAX_MESSAGE_SIZE];
            sscanf(buffer, "%s", command);

            MessageType mt = to_message_type(command);
            switch (mt) {
                case MT_STOP:
                    stop(&msg, true);
                    break;
                case MT_LIST:
                    list(&msg);
                    break;
                case MT_SEND_ALL:
                    sscanf(buffer, "%*s %[^\r\n]", message);
                    strcpy(msg.message, message);
                    send_to_all(&msg);
                    break;
                case MT_SEND_ONE:
                    sscanf(buffer, "%*s %d %[^\r\n]", &client_id, message);
                    msg.to_client_id = client_id;
                    strcpy(msg.message, message);
                    send_to_one(&msg);
                    break;
                default:
                    break;
            }
        }
    }

    return 0;
}