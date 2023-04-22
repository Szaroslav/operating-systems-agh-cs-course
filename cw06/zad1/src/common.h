#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdlib.h>
#include <sys/types.h>

#define HOME                getenv("HOME")
#define SERVER_ID           1
#define MAX_CLIENTS_NUMBER  16
#define MAX_MESSAGE_SIZE    512

typedef enum MessageType {
    MT_INIT     = 1,
    MT_LIST     = 2,
    MT_SEND_ALL = 3,
    MT_SEND_ONE = 4,
    MT_MESSAGE  = 5,
    MT_STOP     = 6
} MessageType;

typedef struct Message {
    long mtype;
    int client_id;
    int to_client_id;
    key_t client_queue_key;
    char message[MAX_MESSAGE_SIZE];
} Message;

#define MESSAGE_SIZE sizeof(Message)

#endif // __COMMON_H__