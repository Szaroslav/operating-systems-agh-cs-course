#include "elf.h"
#include "common.h"
#include <stdio.h>
#include <unistd.h>

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
        
        // Elf's waiting for Santa to solve the issue
        if (*args->waiting_elf_count < MAX_ISSUE_NUMBER) {
            args->waiting_elves[(*args->waiting_elf_count)++] = args->index;
            snprintf(
                msg_buffer, BUFFER_SIZE,
                "Waiting for Santa to solve an issue. Currently are " BOLD_STYLE "%d" RESET_STYLE " elves waiting",
                *args->waiting_elf_count
            );
            print_msg(prefix, msg_buffer);

            // This elf is the last one waiting in the queue for Santa,
            // thus wakes him up
            if (*args->waiting_elf_count == MAX_ISSUE_NUMBER) {
                print_msg(prefix, "Waking up Santa");
                pthread_cond_broadcast(args->santa_wakeup_condition);
            }

            pthread_cond_wait(args->elf_solution_condition, args->mutex);

            print_msg(prefix, "My issue has been solved. Back to work");
            // (*args->waiting_elf_count)--;
        }
        // Elf's solving the issue by theirself
        else if (*args->waiting_elf_count >= MAX_ISSUE_NUMBER) {
            print_msg(prefix, "There are " BOLD_STYLE "3" RESET_STYLE " elves waiting for Santa. Solving it by myself and back to work");
        }

        pthread_mutex_unlock(args->mutex);
    }

    return NULL;
}