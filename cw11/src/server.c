#include "common.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define FILE_TO_READ "output.txt"


int main()
{
    printf("[Server] Started\n\n");

    int flags = 0;
    const int socket_fd = socket(AF_INET, SOCK_DGRAM, flags);
    if (socket_fd == -1) {
        perror("socket() error");
        return EXIT_FAILURE;
    }

    sockaddr_in_t server_addr, client_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    server_addr.sin_family      = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port        = htons(PORT);

    if (bind(socket_fd, (sockaddr_t *) &server_addr, sizeof(server_addr)) == -1) {
        perror("bind() error");
        return EXIT_FAILURE;
    }

    char buffer[BUFFER_SIZE] = "";
    socklen_t length = sizeof(client_addr);
    const int bytes = recvfrom(
        socket_fd, buffer, BUFFER_SIZE, MSG_WAITALL, (sockaddr_t *) &client_addr, &length);
    if (bytes == -1) {
        perror("recvfrom() error");
        return EXIT_FAILURE;
    }

    // Read file

    printf("\n[Server] Finished\n");
    return EXIT_SUCCESS;
}
