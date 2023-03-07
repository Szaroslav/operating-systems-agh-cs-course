#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/times.h>
#include <unistd.h>

#ifndef DYNAMIC
#include "count.h"
#else
#include <dlfcn.h>

typedef struct CounterArray {
    char **counterArray;
    size_t max_size;
    size_t size;
} CounterArray;
#endif // DYNAMIC


#define BUFFER_SIZE 256

int main(int argc, char **argv) {
    #ifdef DYNAMIC

    void *handle = dlopen("libcount_dynamic.so", RTLD_LAZY);
    if (!handle) {
        printf("Failed to dlopen libcount_dynamic.so");
        return -1;
    }

    CounterArray (*init_counter_array)(int);
    void (*count_wl_file)(CounterArray *, char *);
    char* (*get_block_by_index)(CounterArray *, int);
    void (*delete_block_by_index)(CounterArray *, int);
    void (*free_array)(CounterArray *);

    init_counter_array = (CounterArray (*)(int)) dlsym(handle, "init_counter_array");
    count_wl_file = (void (*)(CounterArray *, char *)) dlsym(handle, "count_wl_file");
    get_block_by_index = (char* (*)(CounterArray *, int)) dlsym(handle, "get_block_by_index");
    delete_block_by_index = (void (*)(CounterArray *, int)) dlsym(handle, "delete_block_by_index");
    free_array = (void (*)(CounterArray *)) dlsym(handle, "free_array");

    #endif // DYNAMIC

    char buffer[BUFFER_SIZE];
    char cmd[BUFFER_SIZE];
    CounterArray array;

    while (strcmp(cmd, "exit") != 0) {
        fgets(buffer, BUFFER_SIZE, stdin);
        sscanf(buffer, "%s", cmd);

        // Time
        struct timespec start_ts, end_ts;
        clock_gettime(CLOCK_REALTIME, &start_ts);
        struct tms start_tms, end_tms;
        times(&start_tms);

        if (strcmp(cmd, "init") == 0) {
            int size;
            sscanf(buffer, "%*s %d", &size);
            array = init_counter_array(size);
        }
        else if (strcmp(cmd, "count") == 0) {
            char filename[BUFFER_SIZE];
            sscanf(buffer, "%*s %s", filename);
            count_wl_file(&array, filename);
        }
        else if (strcmp(cmd, "show") == 0) {
            int i;
            sscanf(buffer, "%*s %d", &i);
            printf("%s", get_block_by_index(&array, i));
        }
        else if (strcmp(cmd, "delete") == 0) {
            int i;
            sscanf(buffer, "%*s %d", &i);
            delete_block_by_index(&array, i);
        }
        else if (strcmp(cmd, "destroy") == 0) {
            free_array(&array);
        }

        if (strcmp(cmd, "exit") != 0) {
            // Time
            clock_gettime(CLOCK_REALTIME, &end_ts);
            times(&end_tms);
            printf("Realtime [ns]: %ld, user [s]: %f, system [s]: %f\n",
                end_ts.tv_nsec - start_ts.tv_nsec,
                end_tms.tms_cutime - start_tms.tms_cutime / (double) CLOCKS_PER_SEC,
                end_tms.tms_cstime - start_tms.tms_cstime / (double) CLOCKS_PER_SEC
            );
        } 
    }

    #ifdef DYNAMIC
    dlclose(handle);
    #endif // DYNAMIC

    return 0;
}