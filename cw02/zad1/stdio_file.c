#include "stdio_file.h"
#include <stdio.h>

void stdf_replace_chars(char *input_file, char *output_file, char from, char to) {
    FILE *input_fp = fopen(input_file, "r");
    FILE *output_fp = fopen(output_file, "w");
    char buffer;

    while (fread(&buffer, sizeof(char), 1, input_fp) != 0) {
        if (buffer == from) {
            buffer = to;
        }
        fwrite(&buffer, sizeof(char), 1, output_fp);
    }


    fclose(input_fp);
    fclose(output_fp);
}