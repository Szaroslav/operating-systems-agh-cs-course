#include "common.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main()
{
    printf("[Client] Started\n\n");

    int flags = 0;
    const int socket_fd = socket(AF_INET, SOCK_DGRAM, flags);
    if (socket_fd == -1) {
        perror("socket() error");
        return EXIT_FAILURE;
    }

    sockaddr_in_t server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family      = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port        = htons(PORT);

    char buffer[BUFFER_SIZE] = "INIT";
    const int bytes = sendto(
        socket_fd, buffer, sizeof(buffer), MSG_CONFIRM, (sockaddr_t *) &server_addr, sizeof(server_addr));
    if (bytes == -1) {
        perror("recvfrom() error");
        return EXIT_FAILURE;
    }

    socklen_t length = sizeof(server_addr);

    // Read file

    printf("\n[Client] Finished\n");
    return EXIT_SUCCESS;
}
