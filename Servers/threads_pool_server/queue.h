#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "../config.h"

#include <sys/ipc.h>
#include <sys/socket.h>
#include <netinet/in.h>

//System V 
struct message_text{
    int socket_server;
    char name_client[SIZE_CLIENT_NAME];
    struct sockaddr_in client;
};
//System V 
struct message{
    long message_type;
    struct message_text message_text;
};


#endif