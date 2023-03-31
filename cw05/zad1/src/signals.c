#include "signals.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

enum Signal parse_signal(const char *command) {
    if (strcmp(command, "ignore") == 0) {
        return SIG_IGNORE;
    }
    else if (strcmp(command, "handler") == 0) {
        return SIG_HANDLER;
    }
    else if (strcmp(command, "mask") == 0) {
        return SIG_MASK;
    }
    else if (strcmp(command, "pending") == 0) {
        return SIG_PENDING;
    }

    fprintf(stderr, "Unknown signal type: %s\n", command);
    exit(1);
}