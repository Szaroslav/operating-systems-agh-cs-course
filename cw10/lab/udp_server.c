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
    int status, gniazdo, l_bajtow;
    socklen_t dlugosc;
    struct sockaddr_in ser, cli;
    char buf[200];

    gniazdo = socket(AF_INET, SOCK_DGRAM, 0);
    if (gniazdo == -1) {
        printf("Socket error\n");
        return 1;
    }

    memset(&ser, 0, sizeof(ser));
    ser.sin_family = AF_INET;
    ser.sin_port = htons(9001);
    ser.sin_addr.s_addr = htonl(INADDR_ANY); // inet_addr("127.0.0.1");
    status = bind(gniazdo, (struct sockaddr *) &ser, sizeof(ser));
    if (status == -1) {
        perror("Bind error");
        return 2;
    }

    // status = listen(gniazdo, 10);
    // if (status == -1) {
    //     printf("Listen error\n");
    //     return 3;
    // }

    while (1) {
        dlugosc = sizeof(cli);
        l_bajtow = recvfrom(gniazdo, buf, sizeof(buf), 0, (struct sockaddr *) &cli, &dlugosc);
        buf[l_bajtow] = 0;
        printf("Received: %s\n", buf);
        fflush(stdout);
        
        if (l_bajtow > 0) {
            l_bajtow = sendto(gniazdo, buf, strlen(buf), 0, (struct sockaddr *) &cli, &dlugosc);
        }
    }

    close(gniazdo);
    return 0;
}
