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
    int gniazdo, dlugosc, l_bajtow;
    socklen_t slen;
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
    ser.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    l_bajtow = sendto(gniazdo, "Request from the client", 20, 0, (struct sockaddr *) &ser, sizeof(ser));
    dlugosc = sizeof(cli);
    l_bajtow = recvfrom(gniazdo, buf, sizeof(buf), 0, (struct sockaddr *) &ser, &slen);
    if (l_bajtow > 0) {
        buf[l_bajtow] = '\0';
        printf("Received: %s\n", buf);
    }

    close(gniazdo);
    return 0;
}
