#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv) {
    // pid_t pid;
    // int fd[2];
    // int w;
    // char buffer[BUFSIZ];

    // pipe(fd);
    // if ((pid = fork()) == 0) {
    //     close(fd[0]);
    //     w = write(fd[1], "Gitara siema", 13);
    //     sleep(3);

    //     return 0;
    // }

    // w = read(fd[0], buffer, 13);
    // printf("%s\n", buffer);
    // fflush(stdout);

    // return 0;


    // int fd[2], w;
    // pipe(fd);

    // if (fork() == 0) {
    //     close(fd[0]);
    //     d = write(fd[1], "text", 5);
    //     printf("sent %d bytes\n", d);
        
    //     return 0;
    // }
    // else {
    //     char buffer[10];
    //     close(fd[1]);
    //     dup2(fd[0], STDIN_FILENO);
    //     execlp("grep", "grep", "ako, NULL");
    //     printf("%d bytes: %s\n", d, buffer);

    //     return 0;
    // }


    // FILE *ws;
    // ws = popen("grep syka", "w");
    // fputs("text from stdin\n", ws);
    // pclose(ws);

    // return 0;

    // int w1;
    // char buffer[1024];

    // mkfifo("potok1", S_IFIFO | S_IRWXU);

    // w1 = open("potok1", O_WRONLY);
    // write(w1, "1234567890", 11);
    // close(w1);

    // w1 = open("potok1", O_RDONLY);
    // read(w1, buffer, 11);
    // printf("received: %s\n", buffer);
    // close(w1);

    // return 0;
}