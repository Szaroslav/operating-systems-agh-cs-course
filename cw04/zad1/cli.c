#include "cli.h"
#include <stdio.h>
#include <string.h>

int cli_verify_args(int argc, char **argv) {
    int flag = 0;

    if (argc < 2) {
        fprintf(stderr, "You passed too few arguments (at least 1)\n");
        flag = -1;
    }
    // ignore, handler, mask lub pending
    if (argc > 1) {    
        const char *sig_types[] = {
            "ignore",
            "handler",
            "mask",
            "pending"
        };
        const int n = sizeof(sig_types) / sizeof(sig_types[0]);

        int c = 0;
        for (int i = 0; i < n; i++) {
            if (strcmp(argv[1], sig_types[i]) != 0) c++;
        }

        if (c == n) {
            fprintf(stderr, "%s is a wrong signal type\n", argv[1]);
            flag = -1;
        }
    }

    return flag;
}