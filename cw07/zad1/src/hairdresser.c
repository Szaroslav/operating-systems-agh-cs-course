#include "common.h"
#include "semaphore.h"
#include <stdio.h>

Status status;

int main(int argc, char **argv) {
    printf("[Hairdresser] Spawned\n");

    status = S_IDLE;
    
    smp_init(HAIRDRESSER);
    smp_open();

    return 0;
}