#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdlib.h>

#define HOME                    getenv("HOME")
#define SEMAPHORE_ID            1
#define HAIRDRESSERS_TOTAL      4               // M
#define CHAIRS_TOTAL            4               // N
#define QUEUE_SIZE              8               // P
#define CLIENTS_TOTAL           16

#ifdef SYSTEMV
    #define HAIRDRESSER_PATH        "build/hairdresser_SYSTEMV"
    #define HAIRDRESSER_EXEC        "hairdresser_SYSTEMV"
    #define CLIENT_PATH             "build/client_SYSTEMV"
    #define CLIENT_EXEC             "client_SYSTEMV"
    #define HAIRDRESSER_SEM_NAME    "1"
    #define CHAIR_SEM_NAME          "2"
    #define QUEUE_SEM_NAME          "3"
    #define QUEUE_NAME              "4"
#endif // SYSTEMV

#ifdef POSIX
    #define HAIRDRESSER_PATH        "build/hairdresser_POSIX"
    #define HAIRDRESSER_EXEC        "hairdresser_POSIX"
    #define CLIENT_PATH             "build/client_POSIX"
    #define CLIENT_EXEC             "client_POSIX"
    #define HAIRDRESSER_SEM_NAME    "/hairdresser_sem"
    #define CHAIR_SEM_NAME          "/chair_sem"
    #define QUEUE_SEM_NAME          "/queue_sem"
    #define QUEUE_NAME              "/queue"
#endif // POSIX

#endif // __COMMON_H__