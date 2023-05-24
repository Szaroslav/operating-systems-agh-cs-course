#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>


int main()
{
    int status, gniazdo, dlugosc, nr = 0, end = 1, gniazdo2;
    struct sockaddr_in ser, cli;
    char buf[200];

    gniazdo = socket(AF_INET, SOCK_STREAM, 0);
    if (gniazdo == -1) {
        printf("Socket error\n");
        return 1;
    }

    memset(&ser, 0, sizeof(ser));
    ser.sin_family = AF_INET;
    ser.sin_port = htons(9000);
    ser.sin_addr.s_addr = htonl(INADDR_ANY); // inet_addr("127.0.0.1");
    status = bind(gniazdo, (struct sockaddr *) &ser, sizeof(ser));
    if (status == -1) {
        perror("Bind error");
        return 2;
    }

    status = listen(gniazdo, 10);
    if (status == -1) {
        printf("Listen error\n");
        return 3;
    }

    while (end) {
        dlugosc = sizeof(cli);
        gniazdo2 = accept(gniazdo, (struct sockaddr *) &cli, (socklen_t *) &dlugosc);
        if (gniazdo2 == -1) {
            printf("Accept error\n");
            return 4;
        }

        read(gniazdo2, buf, sizeof(buf));
        if (buf[0] == 'Q') {
            sprintf(buf, "Closing the server\n");
            end = 0;
        }
        else if (buf[0] == 'N') {
            sprintf(buf, "You're client no. %d\n", nr++);
        }
        else {
            sprintf(buf, "Wrong request\n");
        }
        write(gniazdo2, buf, strlen(buf));
        close(gniazdo2);
    }

    close(gniazdo);
    return 0;
}
