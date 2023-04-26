#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>

pthread_t t1, t2;

void* f(void *ptr) {
    static int a = 0;
    int b;

    while (1) {
        b = a;
        // sleep(1);
        a = b + 1;
        printf("(%d) %s\n", a, (char *) ptr);
        fflush(stdout);
        sleep(1);
    }
}

int main(int argc, char **argv) {
    printf("%d\n\n", argc);

    int fd = open("/dev/tty", O_RDWR);
    char buffer[BUFSIZ];
    read(fd, buffer, BUFSIZ);
    printf("%s\n", buffer);

    int i;
    pthread_create(&t1, NULL, &f, "Hello");
    pthread_create(&t2, NULL, &f, "Kitty");

    for (i = 1; i < 10000; i++) {
        // printf("%d ", i);
        // fflush(stdout);
        sleep(5);
    }
}