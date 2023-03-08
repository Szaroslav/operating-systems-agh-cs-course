#include "count.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

CounterArray init_counter_array(int size) {
    CounterArray array;
    array.counterArray = (char**) calloc(size, sizeof(char*));
    array.max_size = size;
    array.size = 0;

    return array;
}

void count_wl_file(CounterArray *array, char *filename) {
    char cmd[BUFFER_SIZE];
    snprintf(cmd, BUFFER_SIZE - 1, "wc %s > /tmp/count_file", filename);
    system(cmd);

    FILE *fp = fopen("/tmp/count_file", "r");
    if (fp == NULL) {
        perror("fopen() failed");
        return;
    }

    char output[BUFFER_SIZE];
    if (fgets(output, BUFFER_SIZE, fp) == NULL) {
        printf("Failure");
        return;
    }
    fclose(fp);

    if (array->size >= array->max_size) {
        printf("Max size reached");
        return;
    }

    size_t n = strlen(output);
    array->counterArray[array->size] = calloc(n, sizeof(char) * n);
    array->counterArray[array->size] = strcpy(array->counterArray[array->size], output);
    array->size++;

    system("rm -f /tmp/count_file");
}

char* get_block_by_index(CounterArray *array, int index) {
    if (index >= array->max_size || index >= array->size)
        return "GET_REKT";
    return array->counterArray[index];
}

void delete_block_by_index(CounterArray *array, int index) {
    free(array->counterArray[index]);
}

void free_array(CounterArray *array) {
    for (int i = 0; i < array->size; i++)
        free(array->counterArray[i]);
    free(array->counterArray);
}