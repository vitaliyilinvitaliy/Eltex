#ifndef _THREAD_CLIENT_H_
#define _THREAD_CLIENT_H_

#include "../config.h"

#include <netinet/in.h>
#include <sys/socket.h>

struct pthread_args
{
    int socket_server;
    char name_client[SIZE_CLIENT_NAME];
    struct sockaddr_in client;
    socklen_t size_cl;
};


void *ThreadClient(void *);

#endif //_THREAD_CLIENT_H_