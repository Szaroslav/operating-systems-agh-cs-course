#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

enum SortingKey {
    SENDER,
    DATE
};

void list_all_mails(const enum SortingKey key) {
    FILE *pptr;

    switch (key) {
        case SENDER:    pptr = popen("mail | tail -n +3 | sort -k3", "w"); break;
        case DATE:      pptr = popen("mail | tail -n +3", "w"); break;
    }

    fputs("exit", pptr);
    pclose(pptr);
}

void send_mail(const char *email_address, const char *subject, const char *content) {
    char buffer[BUFSIZ];
    snprintf(buffer, BUFSIZ, "mail -s %s %s", subject, email_address);

    FILE *pptr = popen(buffer, "w");
    fputs(content, pptr);
    pclose(pptr);
}

int main(int argc, char **argv) {
    // List all mails
    if (argc == 2) {
        enum SortingKey key;

        if (!strcmp(argv[1], "nadawca")) {
            key = SENDER;
        }
        else if (!strcmp(argv[1], "data")) {
            key = DATE;
        }
        else {
            fprintf(stderr, "[ARG ERROR] %s is not an allowed sorting key [nadawca | data]\n", argv[1]);
            return -1;
        }

        list_all_mails(key);
    }
    // Send a mail
    else if (argc == 4) {
        send_mail(argv[1], argv[2], argv[3]);
    }
    else {
        fprintf(stderr, "[ARG ERROR] Wrong number of arguments (1 or 3)\n");
        return -1;
    }

    return 0;
}