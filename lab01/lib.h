typedef struct CountersArray {
    char **counters;
    int max_size;
    int size;
} CountersArray;

CountersArray init_counter_array(int size);
void count_wl_file(CountersArray *array, char *filename);
char* get_line_by_index(CountersArray *array, int index);
void delete_line_by_index(CountersArray *array, int index);
void free_array(CountersArray *array);