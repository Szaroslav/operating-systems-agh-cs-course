#include "santa.h"
#include "common.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *santa_routine(void *arg) {
    ThreadArgs *args = (ThreadArgs *) arg;
    int delivery_count = 0;
    char msg_buffer[BUFFER_SIZE] = "";

    print_spawn(SANTA_PREFIX);

    while (true) {
        pthread_mutex_lock(args->mutex);
        pthread_cond_wait(args->santa_wakeup_condition, args->mutex);
        print_msg(SANTA_PREFIX, "Bloody hell, what's it this time?");

        *args->delivery_duration = range(SANTA_DELIVERY_DURATION.start, SANTA_DELIVERY_DURATION.end);
        snprintf(msg_buffer, BUFFER_SIZE, "Delivering toys for %.2f s", (double) *args->delivery_duration / SEC_TO_USEC);
        print_msg(SANTA_PREFIX, msg_buffer);

        pthread_cond_broadcast(args->reindeer_delivery_condition);
        pthread_mutex_unlock(args->mutex);

        usleep(*args->delivery_duration);
        (*args->delivery_count)++;
        print_msg(SANTA_PREFIX, "Delivery has been finished");

        if (*args->delivery_count >= 3) {
            pthread_exit(NULL);
        }

        pthread_cond_b
    }

    return NULL;
}