#include "../config.h"
#include "../handler_error.h"
#include "thread_client.h"

#include <pthread.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

//gcc ./multithreaded_server/server.c ./multithreaded_server/thread_client.c ./time/time.c -lpthread -o serv_multi

int ServerNtpMultithreaded(void);

int main(void){
    return ServerNtpMultithreaded();
}

int ServerNtpMultithreaded(void){
    int counter_clients = 0;
    int fd_socket_server = -1;
    char name_client[SIZE_CLIENT_NAME] = {0};

    struct sockaddr_in server, client;

    socklen_t size_sockaddr_in = sizeof(struct sockaddr_in);

    fd_socket_server = socket(AF_INET, SOCK_DGRAM, 0);

    if(fd_socket_server == -1){
        handler_error("socket");
    }

    memset((void *)&server, 0, size_sockaddr_in);
    memset((void *)&client, 0, size_sockaddr_in);

    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if(bind(fd_socket_server, (struct sockaddr*)&server, size_sockaddr_in) == -1){
        close(fd_socket_server);
        handler_error("bind");
    }

    socklen_t get_size = 0;
    pthread_t pth_id[MAX_CLIETNS] = {0};
    struct pthread_args *args = (struct pthread_args *) calloc(MAX_CLIETNS, sizeof(struct pthread_args));
    
    while(counter_clients < MAX_CLIETNS){
        get_size = size_sockaddr_in;

        recvfrom(fd_socket_server,(void*)name_client, SIZE_CLIENT_NAME, 0, (struct sockaddr*)&client, &get_size);
    
        args[counter_clients].socket_server = fd_socket_server;
        strncpy(args[counter_clients].name_client, name_client, SIZE_CLIENT_NAME);
        memcpy((void*)&args[counter_clients].client, (void*)&client, size_sockaddr_in);
        args[counter_clients].size_cl = get_size;

        printf("pthread: %d %s\n", args[counter_clients].socket_server, args[counter_clients].name_client);
        
        pthread_create(&pth_id[counter_clients], NULL, ThreadClient, (void*)&args[counter_clients]);    
        counter_clients++;
        if(counter_clients >= 3){
            pthread_join(pth_id[MAX_CLIETNS - 1], NULL);
        }else{
            pthread_detach(pth_id[counter_clients]);
        }
    }

    close(fd_socket_server);
    free(args);
    return 0;
}

