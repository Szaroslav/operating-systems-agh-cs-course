#include "common.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define OUTPUT_FILENAME "./files/output.txt"


int main()
{
    printf("[Client] Started\n");

    // Create the socket
    int flags = 0;
    const int socket_fd = socket(AF_INET, SOCK_DGRAM, flags);
    if (socket_fd == -1) {
        perror("socket() error");
        return EXIT_FAILURE;
    }

    // Initialize server address struct
    sockaddr_in_t server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family      = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port        = htons(PORT);

    char buffer[BUFFER_SIZE] = "";
    while (true) {
        // Get filename from stdin
        printf("\nEnter a filename to read: ");
        if (scanf("%s", buffer) == EOF)
            break;
        
        // Send init message to the server, which contains filename
        socklen_t length = sizeof(server_addr);
        socket_connection_t connection = {
            .socket_fd   = socket_fd,
            .buffer      = buffer,
            .buffer_size = strlen(buffer),
            .flags       = MSG_CONFIRM,
            .addr        = (sockaddr_t *) &server_addr,
            .addr_length = length
        };
        int bytes = sendto_wrapper(&connection);
        if (bytes == -1) {
            perror("sendto() error");
            return EXIT_FAILURE;
        }

        // Receive messages, which contains the file content
        // - print and save them
        printf("=========================================================\n");
        FILE *file = fopen(OUTPUT_FILENAME, "w");
        buffer[0] = 1;
        while (buffer[0]) {
            // Receive
            connection.buffer_size = BUFFER_SIZE;
            connection.flags       = MSG_WAITALL;
            bytes = recvfrom_wrapper(&connection);
            if (bytes == -1) {
                perror("recvfrom() error");
                fclose(file);
                return EXIT_FAILURE;
            }
            // printf("%s", buffer + 1);
            // Save to the output file
            fwrite(buffer + 1, sizeof(char), bytes - (bytes == BUFFER_SIZE ? 1 : 2), file);

            // Send success response
            connection.buffer_size = 1;
            connection.flags       = MSG_CONFIRM;
            bytes = sendto_wrapper(&connection);
            if (bytes == -1) {
                perror("sendto() error");
                fclose(file);
                return EXIT_FAILURE;
            }
        }
        printf("=========================================================\n");

        fclose(file);
    }

    printf("\n\n[Client] Finished\n");
    return EXIT_SUCCESS;
}
