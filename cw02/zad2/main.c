#include "cli.h"
#include "reverse.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

int main(int argc, char **argv) {
    if (cli_verify_args(argc, argv) != 0) {
        return -1;
    }

    char *input_filename = argv[1];
    char *output_filename = argv[2];

    FILE *fp = fopen("pomiar_zad_2.txt", "w");

    struct timespec start_ts, end_ts;
    clock_gettime(CLOCK_REALTIME, &start_ts);
    reverse_file_by_byte(input_filename, output_filename);
    clock_gettime(CLOCK_REALTIME, &end_ts);
    fprintf(fp, "1 byte: %f\n", (end_ts.tv_nsec - start_ts.tv_nsec) / 1000000000.0f);

    clock_gettime(CLOCK_REALTIME, &start_ts);
    reverse_file_by_block(input_filename, output_filename);
    clock_gettime(CLOCK_REALTIME, &end_ts);
    fprintf(fp, "1024 bytes: %f", (end_ts.tv_nsec - start_ts.tv_nsec) / 1000000000.0f);

    fclose(fp);
    return 0;
}