#include "common.h"
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <unistd.h>

// mqd_t sqd;
// mqd_t client_queues[MAX_CLIENTS_NUMBER] = { 0 };
// uint current_queue_size = 0;
// Message msg;
// int fd;

Message message;
int client_socket_fds[MAX_CLIENTS_NUMBER];
int client_socket_fd_size = 0;


// int get_client_id() {
//     if (current_queue_size >= MAX_CLIENTS_NUMBER)
//         return -1;
    
//     for (int i = 0; i < MAX_CLIENTS_NUMBER; i++)
//         if (client_queues[i] == 0)
//             return i;

//     return -1;
// }

// void mt_to_string(MessageType mt, char *buf) {
//     switch (mt) {
//         case MT_STOP:
//             strcpy(buf, "STOP");
//             break;
//         case MT_INIT:
//             strcpy(buf, "INIT");
//             break;
//         case MT_LIST:
//             strcpy(buf, "LIST");
//             break;
//         case MT_SEND_ALL:
//             strcpy(buf, "2ALL");
//             break;
//         case MT_SEND_ONE:
//             strcpy(buf, "2ONE");
//             break;
//         default:
//             strcpy(buf, "");
//     }
// }

// void save_output_to_file() {
//     char curr_time[64];
//     time_t t = time(NULL);
//     struct tm tm = *localtime(&t);
//     snprintf(curr_time, 64, "%d-%02d-%02d %02d:%02d:%02d",
//         tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec
//     );

//     char mt[64];
//     mt_to_string(msg.message_type, mt);

//     char buffer[BUFSIZ];
//     buffer[0] = '\0';
//     int l = snprintf(buffer, BUFSIZ, "%s\tclient id: %d\t%s\n", curr_time, msg.client_id, mt);
//     write(fd, buffer, l);
// }


// void on_stop() {
//     printf("\n[Server] Receive STOP message\n");
//     printf("[Server] Client ID: %d\n", msg.client_id);

//     printf("[Server] Removing the client queue... ");

//     if (client_queues[msg.client_id] == 0) {
//         printf("Failed\n");
//         return;
//     }

//     client_queues[msg.client_id] = 0;
//     current_queue_size--;
//     printf("Succeed\n");
// }

// void on_list() {
//     printf("\n[Server] Receive LIST message\n");
//     printf("[Server] Client ID: %d\n", msg.client_id);

//     int cid = msg.client_id;

//     char buffer[MAX_MESSAGE_SIZE];
//     buffer[0] = '\0';
//     for (int id = 0; id < MAX_CLIENTS_NUMBER; id++) {
//         if (client_queues[id] == 0)
//             continue;
        
//         char id_str[8];
//         sprintf(id_str, "%d", id);
//         strcat(buffer, id_str);
//         if (id == cid)
//             strcat(buffer, " (you)");
//         strcat(buffer, "\n");
//     }
    
//     printf("[Server] Responding to client with list of all clients... ");
//     msg.message_type = MT_LIST; strcpy(msg.message, buffer);
//     if (mq_send(client_queues[cid], (char *) &msg, MESSAGE_SIZE, DEFAULT_PRIORITY) == -1) {
//         printf("Failed\n");
//         return;
//     }
//     printf("Succeed\n");
// }

// void send_to_one(const int cid, Message *msg) {
//     if (cid < 0 || cid >= MAX_CLIENTS_NUMBER || client_queues[cid] == 0) {
//         printf("[Server] Sending a message to %d is disallowed\n", cid);
//         return;
//     }

//     mq_send(client_queues[cid], (char *) &msg, MESSAGE_SIZE, DEFAULT_PRIORITY);
// }

// void on_send_to_all() {
//     printf("\n[Server] Receive 2ALL message\n");
//     printf("[Server] Client ID: %d\n", msg.client_id);

//     int cid = msg.client_id;
//     Message new_msg = { .message_type = MT_MESSAGE, .client_id = msg.client_id };
//     strcpy(new_msg.message, msg.message);

//     for (int id = 0; id < MAX_CLIENTS_NUMBER; id++) {
//         if (client_queues[id] == 0 || id == cid)
//             continue;
        
//         send_to_one(id, &new_msg);
//     }
// }

// void on_send_to_one() {
//     printf("\n[Server] Receive 2ONE message\n");
//     printf("[Server] Client ID: %d\n", msg.client_id);

//     Message new_msg = { .message_type = MT_MESSAGE, .client_id = msg.client_id };
//     strcpy(new_msg.message, msg.message);

//     send_to_one(msg.to_client_id, &new_msg);
// }

// void on_sigint(int signum) {
//     exit(1);
// }

// void onexit() {
//     if (fd > 0)
//         close(fd);

//     msg.message_type = MT_STOP;
//     int cid = msg.client_id;
//     for (int id = 0; id < MAX_CLIENTS_NUMBER; id++) {
//         if (client_queues[id] > 0) {
//             mq_send(client_queues[cid], (char *) &msg, MESSAGE_SIZE, MT_STOP);
//             mq_receive(sqd, (char *) &msg, MESSAGE_SIZE, NULL);
//             on_stop();
//         }
//     }
    
//     printf("[Server] Deleting queue... ");
//     if (mq_unlink(SERVER_NAME) == -1) {
//         printf("Failed\n");
//         return;
//     }
//     printf("Succeed\n");

//     printf("\n[Server] Stopped\n");
// }

void *socket_routine(void *);
void on_init(const int);
void on_stop();
void on_list();
void on_send_one();
void on_send_all();

int main(int argc, char **argv)
{
    printf("[Server] Started\n\n");

    pthread_t socket_thread;
    pthread_create(&socket_thread, NULL, socket_routine, NULL);
    pthread_join(socket_thread, NULL);

    // struct sigaction action;
    // action.sa_handler = on_sigint;
    // sigaction(SIGINT, &action, NULL);

    // atexit(onexit);

    // printf("[Server] Opening output file... ");
    // fd = open("results.txt", O_CREAT | O_WRONLY, 0664);
    // if (fd == -1) {
    //     printf("Failed\n");
    //     return -1;
    // }
    // printf("Succeed\n");

    // printf("[Server] Creating the server queue... ");

    // struct mq_attr smq_attr = {
    //     .mq_maxmsg = 8,
    //     .mq_msgsize = MESSAGE_SIZE,
    //     .mq_curmsgs = 0
    // };

    // sqd = mq_open(SERVER_NAME, O_RDWR | O_CREAT, 0664, &smq_attr);

    // if (sqd == -1) {
    //     printf("Failed\n");
    //     perror("[Server] Server queue");
    //     return -1;
    // }
    // printf("Succeed\n");

    // while (1) {
    //     if (mq_receive(sqd, (char *) &msg, MESSAGE_SIZE, NULL) >= 0) {
    //         save_output_to_file();
            
    //         
    //     }
    // }

    return 0;
}

void *socket_routine(void *arg)
{
    // Create network and local sockets

    // Network socket
    int network_socket;
    if ((network_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("[Error] Failed to create the network socket");
        return NULL;
    }
    struct sockaddr_in network_server_address;
    network_server_address.sin_family = AF_INET;
    network_server_address.sin_port = 2137;
    network_server_address.sin_addr.s_addr = INADDR_ANY;
    bind(network_socket, (struct sockaddr *) &network_server_address, sizeof(network_server_address));
    listen(network_socket, MAX_CLIENTS_NUMBER);

    // Local socket
    // int local_socket;
    // if ((local_socket = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
    //     perror("[Error] Failed to create the local socket");
    //     return NULL;
    // }
    // struct sockaddr_un local_server_address;
    // local_server_address.sun_family = AF_UNIX;
    // strcpy(local_server_address.sun_path, LOCAL_SERVER_PATH);
    // bind(local_socket, (struct sockaddr *) &local_server_address, sizeof(local_server_address));
    // listen(local_socket, MAX_CLIENTS_NUMBER_PER_SOCKET);

    // ===============================================================================

    while (true) {
        int client_socket_fd;
        client_socket_fd = accept(network_socket, NULL, NULL);
        // client_socket_fd = accept(local_socket, NULL, NULL);

        printf("[Server] Accepted the client socket (FD %d)\n", client_socket_fd);
        
        printf("[Server] Receiving a message from the client... ");
        int flags = 0;
        int message_size = recv(client_socket_fd, &message, MESSAGE_SIZE, flags);
        if (message_size == -1) {
            printf("Failed\n");
            perror("Receive error");
        }
        else {
            printf("Succeeded\n");    
        }

        MessageType message_type = message.message_type;
        int client_id;
        if (message_type == MT_INIT) {
            client_id = client_socket_fd_size;
        }
        else {
            client_id = message.client_id;
        }

        printf("[Server] Client ID: %d\n", client_id);

        switch (message_type)
        {
            // case MT_STOP:
            //     on_stop();
            //     break;
            case MT_INIT:
                on_init(client_socket_fd);
                break;
            // case MT_LIST:
            //     on_list();
            //     break;
            // case MT_SEND_ALL:
            //     on_send_all();
            //     break;
            // case MT_SEND_ONE:
            //     on_send_one();
            //     break;
        }

        // printf("Socket!\n");
        // sleep(1);
    }

    // Close the sockets
    close(network_socket);
    // close(local_socket);
    unlink(LOCAL_SERVER_PATH);

    return NULL;
}

void on_init(const int socket_fd) {
    printf("\n[Server] Received INIT message\n");

    if (client_socket_fd_size >= MAX_CLIENTS_NUMBER) {
        printf("[Server] Reached maximum number of clients\n");
        return;
    }

    int client_id = client_socket_fd_size;
    client_socket_fds[client_socket_fd_size++] = socket_fd;

    printf("[Server] Responding to client with its ID... ");
    message.message_type = MT_INIT;
    message.client_id = client_id;
    int flags = 0;
    int bytes_sent = send(socket_fd, &message, MESSAGE_SIZE, flags);
    if (bytes_sent == -1) {
        printf("Failed\n");
        perror("Send error");
    }
    else {
        printf("Succeed\n");
    }
}
