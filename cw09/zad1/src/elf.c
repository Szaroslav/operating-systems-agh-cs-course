#include "elf.h"
#include "common.h"

void *elf_routine(void *arg) {
    ThreadArgs *args = (ThreadArgs *) arg;
    char msg_buffer[BUFFER_SIZE] = "";
    char prefix[SMALL_BUFFER_SIZE] = "";

    pthread_mutex_lock(args->mutex);
    snprintf(prefix, SMALL_BUFFER_SIZE, ELF_PREFIX " %d", args->index);
    print_spawn(prefix);
    pthread_mutex_unlock(args->mutex);

    while (true) {
        const int work_duration = range(ELF_WORK_DURATION.start, ELF_WORK_DURATION.end);
        usleep(work_duration);

        pthread_mutex_lock(args->mutex);
        if (*args->elves_waiting < MAX_ISSUE_NUMBER) {
            (*args->elves_waiting)++;
            msg_buffer = snprintf(
                msg_buffer, BUFFER_SIZE,
                "Waiting for the Santa to solve an issue. Currently are " BOLD_STYLE "%d" RESET_STYLE " elves waiting",
                *args->elves_waiting
            );
            print_msg(prefix, msg_buffer);

            if (*args->elves_waiting == MAX_ISSUE_NUMBER) {
                print_msg(prefix, "Waking up the Santa");
                pthread_cond_broadcast(args->elf_issue_condition);
            }

            pthread_cond_wait(args->elf_issue_condition, args->mutex);
        }
        pthread_mutex_unlock(args->mutex);

        if (*args->reindeers_at_north_pole == REINDEER_NUMBER) {
            print_msg(buffer, "Waking up the Santa");
            pthread_cond_broadcast(args->santa_wakeup_condition);
        }
        
        pthread_cond_wait(args->reindeer_delivery_condition, args->mutex);
        pthread_mutex_unlock(args->mutex);
        usleep(*args->delivery_duration);
    }

    return NULL;
}