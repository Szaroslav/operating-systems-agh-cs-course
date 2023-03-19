#include "reverse.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void reverse_file_by_byte(char *input_file, char *output_file) {
    FILE *input_fp = fopen(input_file, "r");
    FILE *output_fp = fopen(output_file, "w");
    char buffer;
    int i = 0;

    while (fseek(input_fp, --i, SEEK_END) == 0) {
        fread(&buffer, sizeof(char), 1, input_fp);
        fwrite(&buffer, sizeof(char), 1, output_fp);
    }

    fclose(input_fp);
    fclose(output_fp);
}

void reverse_file_by_block(char *input_file, char *output_file) {
    FILE *input_fp = fopen(input_file, "r");
    FILE *output_fp = fopen(output_file, "w");
    char buffer[BLOCK_SIZE];
    ssize_t res;
    int i = 0;

    while (fseek(input_fp, -1 + i-- * BLOCK_SIZE, SEEK_END == 0) && (res = fread(buffer, sizeof(char), BLOCK_SIZE, input_fp)) != 0) {
        char *temp = malloc(sizeof(char) * res);
        for (int i = 0; i < res; i++) temp[i] = buffer[res - 1 - i];
        fwrite(temp, sizeof(char), res, output_fp);
        free(temp);
    }

    fclose(input_fp);
    fclose(output_fp);
}

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