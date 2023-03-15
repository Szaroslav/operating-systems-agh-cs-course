#include "cli.h"
#include "dir_process.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    if (cli_verify_args(argc, argv) != 0) {
        return -1;
    }


    // printf("XDDDD\n");
    // fflush(stdout);
    list_all_files_by_content(argv[1], argv[2]);

    return 0;
}