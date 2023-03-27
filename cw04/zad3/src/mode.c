#include "mode.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

enum Mode parse_mode(const char *mode) {
    if (strcmp(mode, "1") == 0) {
        return M_PNUMS;
    }
    else if (strcmp(mode, "2") == 0) {
        return M_STIME;
    }
    else if (strcmp(mode, "3") == 0) {
        return M_PCHANGES;
    }
    else if (strcmp(mode, "4") == 0) {
        return M_ITIME;
    }
    else if (strcmp(mode, "5") == 0) {
        return M_EXIT;
    }

    fprintf(stderr, "Unknown signal type: %s\n", mode);
    exit(1);
}