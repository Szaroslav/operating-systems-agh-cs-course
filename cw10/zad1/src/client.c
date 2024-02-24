#include "common.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <unistd.h>
#include <signal.h>

Message message;
int id;
int socket_fd;

MessageType to_message_type(const char *);
void *receipt_routine(void *);
void init(const int);
void list(const int);
void on_list(const char *);
void send_all(const int);
void send_one(const int);
void on_message();
void stop(const int, const bool);
void on_sigint(const int);
void _on_exit();

int main(int argc, char **argv)
{
    printf("[Client] Started\n\n");

    // Handle SIGINT signal.
    struct sigaction action;
    action.sa_handler = on_sigint;
    sigaction(SIGINT, &action, NULL);

    // Start thread to receiving messages from the server.
    pthread_t receipt_thread;
    pthread_create(&receipt_thread, NULL, receipt_routine, (void *) &socket_fd);

    const char *domain = argv[2];

    // Network socket.
    if (/*!strcmp(domain, "net")*/ true) {
        if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("[Error] Failed to create the network socket");
            return 1;
        }

        const char *address = argv[1];
        int port            = atoi(argv[2]);
        struct sockaddr_in socket_address;
        socket_address.sin_family = AF_INET;
        socket_address.sin_port = port;
        socket_address.sin_addr.s_addr = INADDR_ANY;

        connect(socket_fd, (struct sockaddr *) &socket_address, sizeof(socket_address));

        init(socket_fd);

        char buffer[32];
        char msg[MAX_MESSAGE_SIZE] = "";
        while (fgets(buffer, 32, stdin) != NULL) {
            char command[32];
            int client_id;
            sscanf(buffer, "%s", command);

            MessageType message_type = to_message_type(command);
            switch (message_type) {
                case MT_STOP:
                    stop(socket_fd, true);
                    break;
                case MT_LIST:
                    list(socket_fd);
                    break;
                case MT_SEND_ALL:
                    sscanf(buffer, "%*s %[^\r\n]", msg);
                    strcpy(message.message, msg);
                    send_all(socket_fd);
                    break;
                case MT_SEND_ONE:
                    sscanf(buffer, "%*s %d %[^\r\n]", &client_id, msg);
                    message.to_client_id = client_id;
                    strcpy(message.message, msg);
                    send_one(socket_fd);
                    break;
            }
        }
    }

    // Local socket
    // else if (!strcmp(domain, "local")) {
    //     if ((socket_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
    //         perror("[Error] Failed to create the local socket");
    //         return 1;
    //     }

    //     struct sockaddr_un socket_address;
    //     socket_address.sun_family = AF_UNIX;
    //     strcpy(socket_address.sun_path, LOCAL_SERVER_PATH);

    //     connect(socket_fd, (struct sockaddr *) &socket_address, sizeof(socket_address));
    // }

    return 0;
}

MessageType to_message_type(const char *str)
{
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

void *receipt_routine(void *args)
{
    int socket_fd = *(int *) args;
    while (true)
    {
        int flags = 0;
        int received_bytes = recv(socket_fd, &message, MESSAGE_SIZE, flags);
        if (received_bytes >= 0) {
            switch (message.message_type) {
                case MT_STOP:
                    pthread_exit(NULL);
                    break;
                case MT_LIST:
                    on_list(message.message);
                    break;
                case MT_MESSAGE:
                    on_message();
                    break;
            }
        }
    }
}

void init(const int socket_fd)
{
    // Send.
    printf("[Client] Sending INIT message to the server... ");

    message.message_type = MT_INIT;
    int flags = 0;
    int sent_bytes = send(socket_fd, &message, MESSAGE_SIZE, flags);
    if (sent_bytes == -1) {
        printf("Failed\n");
        perror("Send error");
    }
    else {
        printf("Succeeded\n");
    }
    // =========

    // Receive.
    printf("[Client] Receiving INIT message from the server... ");

    flags = 0;
    int received_bytes = recv(socket_fd, &message, MESSAGE_SIZE, flags);
    if (received_bytes == -1) {
        printf("Failed\n");
        perror("Receive error");
    }
    else {
        printf("Succeeded\n");
    }
    // =========

    id = message.client_id;
    printf("[Client] Client ID: %d\n\n", id);
}

void list(const int socket_fd)
{
    printf("[Client] Sending LIST message to the server... ");

    message.message_type = MT_LIST;
    message.client_id = id;
    int flags = 0;
    int sent_bytes = send(socket_fd, &message, MESSAGE_SIZE, flags);
    if (sent_bytes == -1) {
        printf("Failed\n");
        perror("Send error");
    }
    else {
        printf("Succeed\n");
    }
}

void on_list(const char *message)
{
    printf("[Client] Received LIST message from the server\n");
    printf("%s\n", message);
}

void send_all(const int socket_fd)
{
    printf("[Client] Sending 2ALL message to the server... ");

    message.message_type = MT_SEND_ALL;
    message.client_id = id;
    int flags = 0;
    int sent_bytes = send(socket_fd, &message, MESSAGE_SIZE, flags);
    if (sent_bytes == -1) {
        printf("Failed\n");
        perror("send error");
        printf("\n");
    }
    else {
        printf("Succeed\n\n");
    }
}

void send_one(const int socket_id)
{
    printf("[Client] Sending 2ONE message to the server... ");

    message.message_type = MT_SEND_ALL;
    message.client_id = id;
    int flags = 0;
    int sent_bytes = send(socket_fd, &message, MESSAGE_SIZE, flags);
    if (sent_bytes == -1) {
        printf("Failed\n");
        perror("send error");
        printf("\n");
    }
    else {
        printf("Succeed\n\n");
    }
}

void on_message()
{
    printf("\n[Client] Receive message from the server\n");
    printf("[Client %d] %s\n", message.client_id, message.message);
    fflush(stdout);
}

void stop(const int socket_fd, const bool send_msg)
{
    if (send_msg) {
        printf("[Client] Sending STOP message to the server... ");

        message.message_type = MT_STOP;
        message.client_id = id;
        int flags = 0;
        int sent_bytes = send(socket_fd, &message, MESSAGE_SIZE, flags);
        if (sent_bytes == -1) {
            printf("Failed\n");
            perror("Send error");
        }
        else {
            printf("Succeed\n");
        }
    }

    close(socket_fd);

    exit(1);
}

void on_sigint(const int signum)
{
    printf("\n[Client] Received SIGINT\n");
    stop(socket_fd, true);
}
