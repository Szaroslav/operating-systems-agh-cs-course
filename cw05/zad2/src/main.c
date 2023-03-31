#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

double get_f_field(double a, double rs, int n) {
    double f = 0.0;
    for (int i = 0; i < n; i++) {
        f += 4 / (pow(a + i * rs, 2) + 1) * rs;
    }

    return f;
}

void init_fds(int **fds, int n) {
    fds = (int **) malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        fds[i] = (int *) malloc(2 * sizeof(int));
}

void free_fds(int **fds, int n) {
    for (int i = 0; i < n; i++)
        free(fds[i]);
    free(fds);
}

int main(int argc, char **argv) {
    if (argc < 3) {
        perror("[ARG ERROR] Too few arguments (at least 2)");
        return -1;
    }

    clock_t start = clock();
    
    double rec_width = atof(argv[1]);
    int n = atoi(argv[2]);
    int m = round(1 / rec_width);

    int **fds = (int **) malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        fds[i] = (int *) malloc(2 * sizeof(int));

    for (int i = 0; i < n; i++) {
        pipe(fds[i]);
        if (fork() == 0) {
            close(fds[i][0]);
            double r = get_f_field((double) i / n, rec_width, m / n);
            write(fds[i][1], &r, sizeof(double));

            return 0;
        }
        else {
            close(fds[i][1]);
        }
    }

    while (wait(NULL) > 0);

    double field = 0.0;
    for (int i = 0; i < n; i++) {
        double r = 0.0;
        read(fds[i][0], &r, sizeof(double));
        field += r;
    }

    for (int i = 0; i < n; i++)
        free(fds[i]);
    free(fds);

    printf("================  Output  ================\n");
    printf("Execution time: %lfs\n", (double) (clock() - start) / CLOCKS_PER_SEC);
    printf("Input arguments:\n");
    printf("N = %d,\trectangle_width = %lf\n", n, rec_width);
    printf("result:\t%lf\n", field);

    fflush(stdout);
    return 0;
}