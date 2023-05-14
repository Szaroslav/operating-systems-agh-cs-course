#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdbool.h>
#include <pthread.h>

#define REINDEER_NUMBER         9
#define ELF_NUMBER              10
#define MAX_ISSUE_NUMBER        3
#define SEC_TO_USEC             1000000
#define SMALL_BUFFER_SIZE       32
#define BUFFER_SIZE             128

#define LIGHT_TEXT_COLOR        "\033[38;5;15m"
#define BOLD_STYLE              "\033[1m"
#define ITALIC_STYLE            "\033[3m"
#define RESET_STYLE             "\033[0m"
#define SANTA_COLOR_STYLE       "\033[48;5;196m"
#define REINDEER_COLOR_STYLE    "\033[48;5;95m"
#define ELF_COLOR_STYLE         "\033[48;5;47m"

typedef struct ThreadArgs {
    int index;
    int seed;

    int *reindeers_at_north_pole;
    int *delivery_duration;
    int *waiting_elves;
    int *waiting_elf_count;

    pthread_mutex_t *mutex;
    pthread_cond_t *santa_wakeup_condition;
    pthread_cond_t *reindeer_delivery_condition;
    pthread_cond_t *elf_solution_condition;
} ThreadArgs;

typedef struct IntervalUSec {
    int start;
    int end;
} IntervalUSec;

extern const IntervalUSec SANTA_SOLUTION_DURATION;
extern const IntervalUSec SANTA_DELIVERY_DURATION;
extern const IntervalUSec REINDEER_HOLIDAYS_DURATION;
extern const IntervalUSec ELF_WORK_DURATION;

int range(const int, const int);
void print_prefix(const char *);
void print_msg(const char *, const char *);
void print_spawn(const char *);

#endif // __COMMON_H__
