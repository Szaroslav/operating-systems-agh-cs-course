#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#define PIPE_PATH "/tmp/pipe"
#define BUFFER_SIZE 64

double f(double x) {
    return 4 / (x*x + 1);
}

double get_f_field(double a, double rs, int n) {
    double field = 0.0;
    for (int i = 0; i < n; i++) {
        field += f(a + i * rs) * rs;
    }

    return field;
}

struct timespec get_time() {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);

    return ts;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        perror("[ARG ERROR] Too few arguments (at least 2)");
        return -1;
    }

    struct timespec start = get_time();
    
    double rec_width = atof(argv[1]);
    int n = atoi(argv[2]);
    int m = round(1 / rec_width);
    int r = m % n;

    char arg1[BUFFER_SIZE];
    char arg2[BUFFER_SIZE];
    char arg3[BUFFER_SIZE];

    mkfifo(PIPE_PATH, 0666);

    for (int i = 0; i < n; i++) {   
        if (fork() == 0) {
            snprintf(arg1, BUFFER_SIZE, "%.16lf", (double) i / n);
            snprintf(arg2, BUFFER_SIZE, "%.16lf", rec_width);
            snprintf(arg3, BUFFER_SIZE, "%d", m / n + (r-- > 0 ? 1 : 0));

            if (execl("build/evaluator", "evaluator", arg1, arg2, arg3, (char *) NULL) == -1) {
                fprintf(stderr, "[EXECL ERROR %d] Cannot execute a program\n", errno);
                return -1;
            }
        }
    }

    // while (wait(NULL) > 0);
    // printf("?\n");
    int pd = open(PIPE_PATH, O_RDONLY);

    double field = 0.0;
    for (int i = 0; i < n;) {
        double r = 0.0;
        int bytes = read(pd, &r, sizeof(double));
        field += r;

        if (bytes > 0)
            i++;
        // printf("[l] %d\n", i);
    }

    close(pd);

    struct timespec end = get_time();
    double time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / pow(10, 9);

    printf("==================  Output  ==================\n");
    printf("Execution time: %lf s\n", time);
    printf("Input arguments:\n");
    printf("N = %d,\trectangle_width = %.12lf\n", n, rec_width);
    printf("Result:\t%lf\n", field);
    printf("==============================================\n");

    fflush(stdout);
    remove(PIPE_PATH);

    return 0;
}