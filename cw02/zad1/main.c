#include "cli.h"
#include "system_file.h"
#include "stdio_file.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

int main(int argc, char **argv) {
    if (cli_verify_args(argc, argv) != 0) {
        return -1;
    }

    const char from_char = argv[1][0];
    const char to_char = argv[2][0];
    char *input_filename = argv[3];
    char *output_filename = argv[4];

    FILE *fp = fopen("pomiar_zad_1.txt", "w");

    struct timespec start_ts, end_ts;
    clock_gettime(CLOCK_REALTIME, &start_ts);
    sf_replace_chars(input_filename, output_filename, from_char, to_char);
    clock_gettime(CLOCK_REALTIME, &end_ts);
    fprintf(fp, "System library of file handling realtime execution time: %f\n", (end_ts.tv_nsec - start_ts.tv_nsec) / 1000000000.0f);

    clock_gettime(CLOCK_REALTIME, &start_ts);
    stdf_replace_chars(input_filename, output_filename, from_char, to_char);
    clock_gettime(CLOCK_REALTIME, &end_ts);
    fprintf(fp, "Standard IO library realtime execution time: %f", (end_ts.tv_nsec - start_ts.tv_nsec) / 1000000000.0f);

    fclose(fp);
    return 0;
}