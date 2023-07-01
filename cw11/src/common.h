#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdbool.h>
#include <sys/socket.h>

#define PORT        9000
#define BUFFER_SIZE 1024

typedef struct sockaddr sockaddr_t;
typedef struct sockaddr_in sockaddr_in_t;

typedef struct socket_connection {
    int socket_fd;
    char *buffer;
    size_t buffer_size;
    int flags;
    sockaddr_t *addr;
    socklen_t addr_length;
} socket_connection_t;

// void trim(char *);
int sendto_wrapper(socket_connection_t *);
int recvfrom_wrapper(socket_connection_t *);

#endif // __COMMON_H__
