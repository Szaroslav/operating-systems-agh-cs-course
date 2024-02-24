#include "common.h"
#include <string.h>

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
