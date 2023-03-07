#ifndef count_h
#define count_h

#include <stdlib.h>

// typedef struct LWCCounter {
//     size_t *lines;
//     size_t *words;
//     size_t *chars;
// } LWCCounter;

typedef struct CounterArray {
    char **counterArray;
    size_t max_size;
    size_t size;
} CounterArray;

CounterArray init_counter_array(int size);
void count_wl_file(CounterArray *array, char *filename);
char* get_block_by_index(CounterArray *array, int index);
void delete_block_by_index(CounterArray *array, int index);
void free_array(CounterArray *array);

#endif // count_h