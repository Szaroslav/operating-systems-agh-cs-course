#include "cli.h"
#include <stdio.h>

int cli_verify_args(int argc, char **argv) {
    if (argc < 4) {
        fprintf(stderr, "You passed too few arguments (minimum 4)\n");
    }
}