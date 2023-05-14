#include "santa.h"
#include "common.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *santa_routine(void *arg) {
    ThreadArgs *args = (ThreadArgs *) arg;
    int delivery_count = 0;
    char msg_buffer[BUFFER_SIZE] = "";

    pthread_mutex_lock(args->mutex);
    print_spawn(SANTA_PREFIX);
    pthread_mutex_unlock(args->mutex);

    while (true) {
        pthread_mutex_lock(args->mutex);
        print_msg(SANTA_PREFIX, "Going to sleep");
        pthread_cond_wait(args->santa_wakeup_condition, args->mutex);
        print_msg(SANTA_PREFIX, "Bloody hell, what's it this time?");

        // The problem solving
        if (*args->waiting_elf_count == MAX_ISSUE_NUMBER) {
            const int solution_duration = range(SANTA_SOLUTION_DURATION.start, SANTA_SOLUTION_DURATION.end);
            snprintf(
                msg_buffer, BUFFER_SIZE,
                "Solving the issues of elves " BOLD_STYLE "%d %d %d" RESET_STYLE " for %.2f s",
                args->waiting_elves[0], args->waiting_elves[1], args->waiting_elves[2],
                (double) solution_duration / SEC_TO_USEC
            );
            print_msg(SANTA_PREFIX, msg_buffer);
            pthread_mutex_unlock(args->mutex);
            usleep(solution_duration);

            pthread_mutex_lock(args->mutex);
            print_msg(SANTA_PREFIX, "The issues have been solved");
            // Inform the waiting elves, that their issues have been solved
            pthread_cond_broadcast(args->elf_solution_condition);
        }

        // The presents delivery
        if (*args->reindeers_at_north_pole == REINDEER_NUMBER) {
            *args->delivery_duration = range(SANTA_DELIVERY_DURATION.start, SANTA_DELIVERY_DURATION.end);
            snprintf(msg_buffer, BUFFER_SIZE, "Delivering toys for %.2f s", (double) *args->delivery_duration / SEC_TO_USEC);
            print_msg(SANTA_PREFIX, msg_buffer);

            // Harness the reindeers to deliver presents
            pthread_cond_broadcast(args->reindeer_delivery_condition);
            pthread_mutex_unlock(args->mutex);

            usleep(*args->delivery_duration);
            delivery_count++;
            print_msg(SANTA_PREFIX, "The delivery has been finished");

            // Santa's world simulation ending condition
            if (delivery_count >= 3) {
                pthread_exit(NULL);
            }
        }

        pthread_mutex_unlock(args->mutex);
    }

    return NULL;
}