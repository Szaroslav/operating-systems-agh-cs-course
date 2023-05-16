#include "common.h"
#include "santa.h"
#include "reindeer.h"
#include "elf.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

// Shared variables
int reindeers_at_north_pole                 = REINDEER_NUMBER;
int delivery_duration                       = 0;
int waiting_elves[MAX_ISSUE_NUMBER];
int waiting_elf_count                       = 0;

// Mutex and condition variables
pthread_mutex_t mutex                       = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t santa_wakeup_condition       = PTHREAD_COND_INITIALIZER;
pthread_cond_t reindeer_delivery_condition  = PTHREAD_COND_INITIALIZER;
pthread_cond_t elf_solution_condition       = PTHREAD_COND_INITIALIZER;

ThreadArgs *set_thread_args(ThreadArgs *, const int);
pthread_t spawn_santa(ThreadArgs *);
void spawn_reindeers(pthread_t *, ThreadArgs *);
void spawn_elves(pthread_t *, ThreadArgs *);

int main()
{
    printf(BOLD_STYLE "The world has been started\n" RESET_STYLE);

    srand(time(NULL));
    pthread_t *threads = malloc((REINDEER_NUMBER + ELF_NUMBER) * sizeof(pthread_t));
    ThreadArgs *thread_args = malloc((REINDEER_NUMBER + ELF_NUMBER + 1) * sizeof(ThreadArgs));
    
    spawn_reindeers(threads, thread_args);
    spawn_elves(threads, thread_args);

    pthread_join(spawn_santa(thread_args), NULL);

    // Canceling rest of the threads
    for (int i = 0; i <  REINDEER_NUMBER + ELF_NUMBER; i++)
        pthread_cancel(threads[i]);

    // Deallocating memory
    free(threads);
    free(thread_args);

    printf(BOLD_STYLE "The world has been finished\n" RESET_STYLE);

    return 0;
}

ThreadArgs *set_thread_args(ThreadArgs *args, const int index) {
    args->index = index;
    args->seed = rand();

    args->reindeers_at_north_pole = &reindeers_at_north_pole;
    args->delivery_duration = &delivery_duration;
    args->waiting_elves = waiting_elves;
    args->waiting_elf_count = &waiting_elf_count;

    args->mutex = &mutex;
    args->santa_wakeup_condition = &santa_wakeup_condition;
    args->reindeer_delivery_condition = &reindeer_delivery_condition;
    args->elf_solution_condition = &elf_solution_condition;

    return args;
}

pthread_t spawn_santa(ThreadArgs *args) {
    set_thread_args(&args[0], 1);
    pthread_t santa_thread;
    pthread_create(&santa_thread, NULL, santa_routine, &args[0]);

    return santa_thread;
}

void spawn_reindeers(pthread_t *threads, ThreadArgs *args) {
    for (int i = 0; i < REINDEER_NUMBER; i++) {
        set_thread_args(&args[1 + i], i + 1);
        pthread_create(&threads[i], NULL, reindeer_routine, (void *) &args[1 + i]);
    }
}

void spawn_elves(pthread_t *threads, ThreadArgs *args) {
    for (int i = 0; i < ELF_NUMBER; i++) {
        set_thread_args(&args[1 + REINDEER_NUMBER + i], i + 1);
        pthread_create(&threads[REINDEER_NUMBER + i], NULL, elf_routine, (void *) &args[1 + REINDEER_NUMBER + i]);
    }
}
