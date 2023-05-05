#include "grid.h"
#include <pthread.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

const int grid_width = 30;
const int grid_height = 30;

char *create_grid()
{
    return malloc(sizeof(char) * grid_width * grid_height);
}

void destroy_grid(char *grid)
{
    free(grid);
}

void draw_grid(char *grid)
{
    for (int i = 0; i < grid_height; ++i)
    {
        // Two characters for more uniform spaces (vertical vs horizontal)
        for (int j = 0; j < grid_width; ++j)
        {
            if (grid[i * grid_width + j])
            {
                mvprintw(i, j * 2, "■");
                mvprintw(i, j * 2 + 1, " ");
            }
            else
            {
                mvprintw(i, j * 2, " ");
                mvprintw(i, j * 2 + 1, " ");
            }
        }
    }

    refresh();
}

void init_grid(char *grid)
{
    for (int i = 0; i < grid_width * grid_height; ++i)
        grid[i] = rand() % 2 == 0;
}

bool is_alive(int row, int col, char *grid)
{
    int count = 0;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
            {
                continue;
            }
            int r = row + i;
            int c = col + j;
            if (r < 0 || r >= grid_height || c < 0 || c >= grid_width)
            {
                continue;
            }
            if (grid[grid_width * r + c])
            {
                count++;
            }
        }
    }

    if (grid[row * grid_width + col])
    {
        if (count == 2 || count == 3)
            return true;
        else
            return false;
    }
    else
    {
        if (count == 3)
            return true;
        else
            return false;
    }
}

void update_grid(char *src, char *dst)
{
    for (int i = 0; i < grid_height; ++i)
    {
        for (int j = 0; j < grid_width; ++j)
        {
            dst[i * grid_width + j] = is_alive(i, j, src);
        }
    }
}

// ==================================================
// ==================================================
// ==================================================

typedef struct ThreadArgs {
    char *src;
    char *dst;
    uint row;
    uint col;
} ThreadArgs;

pthread_t *threads = NULL;
ThreadArgs *args = NULL;

void free_memory()
{
    free(threads);
    free(args);
}

void ignore_handler(int signum) {}

void* update_cell(void *args)
{
    ThreadArgs *thread_args = (ThreadArgs*) args;
    uint i = thread_args->row, j = thread_args->col;

    while (true) {
        thread_args->dst[i * grid_width + j] = is_alive(i, j, thread_args->src);

        pause();

        char *temp = thread_args->src;
        thread_args->src = thread_args->dst;
        thread_args->dst = temp;
    }

    return NULL;
}

void update_grid_concurrent(char *src, char *dst)
{
    // Init threads
    if (threads == NULL) {
        static struct sigaction action;
        sigemptyset(&action.sa_mask);
        action.sa_handler = ignore_handler;
        sigaction(SIGUSR1, &action, NULL);

        threads = malloc(grid_width * grid_height * sizeof(pthread_t));
        args = malloc(grid_width * grid_height * sizeof(ThreadArgs));

        for (int i = 0; i < grid_width * grid_height; i++) {
            args[i].src = src;
            args[i].dst = dst;
            args[i].row = i / grid_width;
            args[i].col = i % grid_height;

            pthread_create(&threads[i], NULL, update_cell, (void*) &args[i]);
        }
    }
    
    for (int i = 0; i < grid_width * grid_height; i++)
        pthread_kill(threads[i], SIGUSR1);
}
