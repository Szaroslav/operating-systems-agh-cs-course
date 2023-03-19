#include "cli.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    if (cli_verify_args(argc, argv) != 0) {
        return -1;
    }

    char *app_name = get_app_name(argv[0]);
    printf("[%s] ", app_name);
    if (app_name != NULL) free(app_name);

    fflush(stdout);
    execl("/bin/ls", "ls", argv[1], (char *) NULL);

    return 0;
}