#include "common.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>


long get_file_size(FILE *);

int main()
{
    printf("[Server] Started\n\n");

    // Create the socket.
    int flags = 0;
    const int socket_fd = socket(AF_INET, SOCK_DGRAM, flags);
    if (socket_fd == -1) {
        perror("socket() error");
        return EXIT_FAILURE;
    }

    // Initialize server and client address structs.
    sockaddr_in_t server_addr, client_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    server_addr.sin_family      = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port        = htons(PORT);

    // Bind the socket to the server address.
    if (bind(socket_fd, (sockaddr_t *) &server_addr, sizeof(server_addr)) == -1) {
        perror("bind() error");
        return EXIT_FAILURE;
    }

    while (true) {
        // Wait for the client's init message.
        char buffer[BUFFER_SIZE] = "";
        socklen_t length = sizeof(client_addr);
        socket_connection_t connection = {
            .socket_fd   = socket_fd,
            .buffer      = buffer,
            .buffer_size = BUFFER_SIZE,
            .flags       = MSG_WAITALL,
            .addr        = (sockaddr_t *) &client_addr,
            .addr_length = length
        };
        int bytes = recvfrom_wrapper(&connection);
        if (bytes == -1) {
            perror("recvfrom() error");
            return EXIT_FAILURE;
        }

        printf("[Server] Established connection with the client\n");
        char filename[BUFFER_SIZE];
        strcpy(filename, buffer);
        printf("[Server] Requested filename: %s\n", filename);

        // Open the requested file.
        snprintf(buffer, BUFFER_SIZE, "./files/%s", filename);
        FILE *file = fopen(buffer, "r");
        if (file == NULL) {
            perror("fopen() error");
            return -1L;
        }

        // Read blocks of bytes of the file.
        while (!feof(file)) {
            size_t read_bytes = fread(buffer + 1, sizeof(char), BUFFER_SIZE - 1, file);
            if (read_bytes < BUFFER_SIZE - 1)
                buffer[read_bytes + 1] = '\0';
            buffer[0] = read_bytes == BUFFER_SIZE - 1 ? 1 : 0;

            connection.buffer_size = buffer[0] ? BUFFER_SIZE : read_bytes + 2;
            connection.flags       = MSG_CONFIRM;
            bytes = sendto_wrapper(&connection);
            if (bytes == -1) {
                perror("sendto() error");
                fclose(file);
                return EXIT_FAILURE;
            }

            connection.buffer_size = BUFFER_SIZE;
            connection.flags       = MSG_WAITALL;
            bytes = recvfrom_wrapper(&connection);
            if (bytes == -1) {
                perror("recvfrom() error");
                fclose(file);
                return EXIT_FAILURE;
            }
        }

        fclose(file);
    }

    close(socket_fd);
    printf("\n[Server] Finished\n");

    return EXIT_SUCCESS;
}

long get_file_size(FILE *file)
{
    // Set file pointer to the end.
    if (fseek(file, 0, SEEK_END) != 0) {
        printf("fseek() error\n");
        return -1L;
    }
    // Get file size.
    long file_size_bytes = ftell(file);
    if (file_size_bytes == -1L) {
        perror("ftell() error");
        return -1L;
    }
    // Set file pointer back to the begining.
    rewind(file);

    return file_size_bytes;
}
