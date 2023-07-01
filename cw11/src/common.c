#include "common.h"
#include <string.h>

// void trim(char *string)
// {
//     const unsigned long n = strlen(string);

//     int i = 0;
//     while (i < n) {
//         if (string[i] != '\n')
//             break;
//         i++;
//     }
//     string = string + i;

//     i = n - 1;
//     while (i >= 0) {
//         if (string[i] != '\n')
//             break;
//         i--;
//     }
//     string[i] = '\0';
// }

int sendto_wrapper(socket_connection_t *sc)
{
    return sendto(
        sc->socket_fd,
        sc->buffer,
        sc->buffer_size,
        sc->flags,
        sc->addr,
        sc->addr_length);
}

int recvfrom_wrapper(socket_connection_t *sc)
{
    return recvfrom(
        sc->socket_fd,
        sc->buffer,
        sc->buffer_size,
        sc->flags,
        sc->addr,
        &sc->addr_length);
}
