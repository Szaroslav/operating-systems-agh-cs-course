#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <mqueue.h>

#define HOME                            getenv("HOME")
#define LOCAL_SERVER_PATH               "/tmp/local_server"
#define MAX_CLIENTS_NUMBER_PER_SOCKET   8
#define MAX_MESSAGE_SIZE                512
#define MAX_QUEUE_NAME_LENGTH           32
#define DEFAULT_PRIORITY                1

typedef enum MessageType {
    MT_INIT     = 1,
    MT_LIST     = 2,
    MT_SEND_ALL = 3,
    MT_SEND_ONE = 4,
    MT_MESSAGE  = 5,
    MT_STOP     = 6
} MessageType;

typedef struct Message {
    int message_type;
    int client_id;
    int to_client_id;
    char client_queue_name[MAX_QUEUE_NAME_LENGTH];
    char message[MAX_MESSAGE_SIZE];
} Message;

#define MESSAGE_SIZE sizeof(Message)

#endif // __COMMON_H__