#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdlib.h>

#define HOME                    getenv("HOME")
#define SEMAPHORE_ID            1
#define HAIRDRESSERS_TOTAL      4               // M
#define CHAIRS_TOTAL            4               // N
#define QUEUE_SIZE              8               // P
#define CLIENTS_TOTAL           16

#define HAIRDRESSER_SEM_NAME    "1"
#define CHAIR_SEM_NAME          "2"
#define QUEUE_SEM_NAME          "3"

typedef enum Person {
    HAIRDRESSER = 0,
    CLIENT      = 1
} Person;

typedef enum Status {
    S_IDLE      = 0,
    S_WORKING   = 1,
    S_CUTTING   = 2,
    S_WAITING   = 3
} Status;

// typedef enum MessageType {
//     MT_INIT     = 1,
//     MT_LIST     = 2,
//     MT_SEND_ALL = 3,
//     MT_SEND_ONE = 4,
//     MT_MESSAGE  = 5,
//     MT_STOP     = 6
// } MessageType;
// 
// typedef struct Message {
//     long mtype;
//     int client_id;
//     int to_client_id;
//     key_t client_queue_key;
//     char message[MAX_MESSAGE_SIZE];
// } Message;
// 
// #define MESSAGE_SIZE sizeof(Message)

#endif // __COMMON_H__