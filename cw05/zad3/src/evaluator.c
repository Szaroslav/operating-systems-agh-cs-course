#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define PIPE_PATH "/tmp/pipe"

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

int main(int argc, char **argv) {
    if (argc < 4) {
        perror("[ARG ERROR] Too few arguments (at least 3)");
        return -1;
    }

    double a = atof(argv[1]);
    double rec_width = atof(argv[2]);
    int n = atoi(argv[3]);

    int pd = open(PIPE_PATH, O_WRONLY);
    double f = get_f_field(a, rec_width, n);
    write(pd, &f, sizeof(double));
    close(pd);

    return 0;
}