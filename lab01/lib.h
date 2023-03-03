typedef struct CounterArray {
    int *counter;
    unsigned int max_size;
    unsigned int size;
} CounterArray;

CounterArray init_counter_array(int size);
void count_wl_file(CounterArray *array, char *filename);
void get_line_by_index(CounterArray *array, int index);
void delete_line_by_index(CounterArray *array, int index);
void free_array(CounterArray *array);