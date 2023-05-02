#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdlib.h>

#define HOME                    getenv("HOME")
#define SEMAPHORE_ID            1
#define HAIRDRESSERS_TOTAL      4               // M
#define CHAIRS_TOTAL            4               // N
#define QUEUE_SIZE              8               // P
#define CLIENTS_TOTAL           16

#define HAIRDRESSER_PATH        "build/hairdresser"
#define HAIRDRESSER_EXEC        "hairdresser"
#define CLIENT_PATH             "build/client"
#define CLIENT_EXEC             "client"
#define HAIRDRESSER_SEM_NAME    "1"
#define CHAIR_SEM_NAME          "2"
#define QUEUE_SEM_NAME          "3"
#define QUEUE_NAME              "4"

#endif // __COMMON_H__