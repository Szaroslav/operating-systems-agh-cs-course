#include "cli.h"
#include "dir_browser.h"

int main(int argc, char **argv) {
    if (cli_verify_args(argc, argv) != 0) {
        return -1;
    }
    
    db_list_all_files(argv[1]);
    
    return 0;
}