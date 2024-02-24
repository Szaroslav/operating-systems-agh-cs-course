#include "common.h"
#include "santa.h"
#include "reindeer.h"
#include "elf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const IntervalUSec SANTA_SOLUTION_DURATION      = { 1 * SEC_TO_USEC, 2 * SEC_TO_USEC };
const IntervalUSec SANTA_DELIVERY_DURATION      = { 2 * SEC_TO_USEC, 4 * SEC_TO_USEC };
const IntervalUSec REINDEER_HOLIDAYS_DURATION   = { 5 * SEC_TO_USEC, 10 * SEC_TO_USEC };
const IntervalUSec ELF_WORK_DURATION            = { 2 * SEC_TO_USEC,  5 * SEC_TO_USEC };

int range(const int start, const int end) {
    return rand() % (end - start) + start;
}

void print_prefix(const char *raw_prefix) {
    // Format stdout to print Santa's prefix.
    if (strstr(raw_prefix, SANTA_PREFIX) != NULL)
        printf(LIGHT_TEXT_COLOR SANTA_COLOR_STYLE);
    // Format stdout to print the reindeer's prefix.
    else if (strstr(raw_prefix, REINDEER_PREFIX) != NULL)
        printf(LIGHT_TEXT_COLOR REINDEER_COLOR_STYLE);
    // Format stdout to print the elf's prefix.
    else if (strstr(raw_prefix, ELF_PREFIX) != NULL)
        printf(LIGHT_TEXT_COLOR ELF_COLOR_STYLE);

    printf(BOLD_STYLE "[%s]" RESET_STYLE " ", raw_prefix);
}

void print_msg(const char *raw_prefix, const char *msg) {
    print_prefix(raw_prefix);
    printf(ITALIC_STYLE "%s\n" RESET_STYLE,  msg);
}

void print_spawn(const char *raw_prefix) {
    print_msg(raw_prefix, "Spawned");
}

void print_array(int *array, int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);
}
