#include "reindeer.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *reindeer_routine(void *arg) {
    ThreadArgs *args = (ThreadArgs *) arg;
    char msg_buffer[BUFFER_SIZE] = "";
    char prefix[SMALL_BUFFER_SIZE] = "";
    const IntervalUSec *rhd = &REINDEER_HOLIDAYS_DURATION;

    pthread_mutex_lock(args->mutex);
    snprintf(prefix, SMALL_BUFFER_SIZE, REINDEER_PREFIX " %d", args->index);
    print_spawn(prefix);

    while (true) {
        // Go on the desired holidays.
        (*args->reindeers_at_north_pole)--;
        if (*args->reindeers_at_north_pole == 0) {
            snprintf(
                msg_buffer, BUFFER_SIZE,
                "Finally, holidays. %d - %d s is perfectly fine to rest :)",
                rhd->start / SEC_TO_USEC, rhd->end / SEC_TO_USEC
            );
            print_msg(REINDEER_GENERAL_PREFIX, msg_buffer);
        }

        pthread_mutex_unlock(args->mutex);

        // Rest for a some peroid of time.
        const int holidays_duration = range(rhd->start, rhd->end);
        usleep(holidays_duration);

        pthread_mutex_lock(args->mutex);
        // Return from the holidays.
        (*args->reindeers_at_north_pole)++;
        snprintf(
            msg_buffer,
            BUFFER_SIZE,
            "Back from holidays. Currently are waiting " BOLD_STYLE "%d" RESET_STYLE " reindeers",
            *args->reindeers_at_north_pole
        );
        print_msg(prefix, msg_buffer);

        // Wake Santa up, if every reindeer came back from the holidays.
        if (*args->reindeers_at_north_pole == REINDEER_NUMBER) {
            print_msg(prefix, "Waking up Santa");
            pthread_cond_broadcast(args->santa_wakeup_condition);
        }

        pthread_cond_wait(args->reindeer_delivery_condition, args->mutex);
    }

    return NULL;
}
