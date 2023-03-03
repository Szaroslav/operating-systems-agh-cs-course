#include "lib.h"

CounterArray init_counter_array(int size) {
    CounterArray array;
    array.counter = (int *) calloc(size, sizeof(int));
    array.max_size = size;
    array.size = 0;

    return array;
}