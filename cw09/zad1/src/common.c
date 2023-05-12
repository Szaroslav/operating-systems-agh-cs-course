#include "common.h"
#include <stdio.h>
#include <stdlib.h>

const IntervalUSec SANTA_SOLUTION_DURATION = { 1 * SEC_TO_USEC, 2 * SEC_TO_USEC };
const IntervalUSec SANTA_DELIVERY_DURATION = { 2 * SEC_TO_USEC, 4 * SEC_TO_USEC };
const IntervalUSec REINDEER_HOLIDAYS_DURATION = { 5 * SEC_TO_USEC, 10 * SEC_TO_USEC };
const IntervalUSec ELF_WORK_DURATION = { 2 * SEC_TO_USEC,  5 * SEC_TO_USEC };

int range(const int start, const int end) {
    return rand() % (end - start) + start;
}

void print_prefix(const char *raw_prefix) {
    printf(BOLD_STYLE "[%s]" RESET_STYLE " ", raw_prefix);
}

void print_msg(const char *raw_prefix, const char *msg) {
    print_prefix(raw_prefix);
    printf(ITALIC_STYLE "%s\n" RESET_STYLE,  msg);
}

void print_spawn(const char *raw_prefix) {
    print_msg(raw_prefix, "Spawned");
}
