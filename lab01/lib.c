#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CountersArray init_counter_array(int size) {
    CountersArray array;
    array.counters = (char **) calloc(size, sizeof(char*));
    array.max_size = size;
    array.size = 0;

    return array;
}

void count_wl_file(CountersArray *array, char *filename) {
    char cmd[256];
    snprintf(cmd, 255, "wc %s | awk '{ print $1, $2, $3 }' > /tmp/count_file", filename);
    system(cmd);

    FILE *fp = fopen("/tmp/count_file", "r");
    if (fp == NULL) {
        perror("fopen() failed");
        return;
    }

    char output[128];
    if (fgets(output, 128, fp) == NULL) {
        printf("Failure");
        return;
    }
    fclose(fp);

    if (array->size >= array->max_size) {
        printf("Max size reached");
        return;
    }

    size_t n = strlen(output);
    array->counters[array->size] = calloc(n, sizeof(char) * n);
    array->counters[array->size] = strcpy(array->counters[array->size], output);
    array->size++;

    system("rm /tmp/count_file");
}

char* get_line_by_index(CountersArray *array, int index) {
    return array->counters[index];
}

void delete_line_by_index(CountersArray *array, int index) {
    free(array->counters[index]);
}

void free_array(CountersArray *array) {
    for (int i = 0; i < array->size; i++)
        free(array->counters[i]);
    free(array->counters);
}