#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

double f(double x) {
    return 4 / (x*x + 1);
}

double get_f_field(double a, double rw, int n) {
    double field = 0.0;
    for (int i = 0; i < n; i++) {
        field += f(a + i * rw) * rw;
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

    int *read_fds = (int *) malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int fds[2];
        pipe(fds);
        read_fds[i] = fds[0];

        if (fork() == 0) {
            close(fds[0]);
            double f = get_f_field((double) i / n, rec_width, m / n + (r-- > 0 ? 1 : 0));
            write(fds[1], &f, sizeof(double));

            return 0;
        }
        else {
            close(fds[1]);
        }
    }

    while (wait(NULL) > 0);

    double field = 0.0;
    for (int i = 0; i < n; i++) {
        double r = 0.0;
        read(read_fds[i], &r, sizeof(double));
        field += r;
    }

    free(read_fds);

    struct timespec end = get_time();
    double time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / pow(10, 9);

    printf("==================  Output  ==================\n");
    printf("Execution time: %lf s\n", time);
    printf("Input arguments:\n");
    printf("N = %d,\trectangle_width = %lf\n", n, rec_width);
    printf("Result:\t%lf\n", field);
    printf("==============================================\n");

    fflush(stdout);
    return 0;
}