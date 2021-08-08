#include "../config.h"
#include "../handler_error.h"
#include "thread_client.h"
#include "queue.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include <sys/ipc.h>
#include <sys/msg.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <pthread.h>

//gcc ./threads_pool_server/server.c ./threads_pool_server/thread_client.c ./time/time.c -lpthread -o serv_pool

extern unsigned int free_threads;

int ServerNtpThreadPool(void);

int main(void){
    return ServerNtpThreadPool();
}

int ServerNtpThreadPool(void){
    char str_time[SIZE_STR_TIME] = {0};
    char str_name[SIZE_CLIENT_NAME] = {0};

    pthread_t mass_threads[SIZE_POOL];

    int fd_socket_server = -1;
    struct sockaddr_in server, client;

    socklen_t size_sockaddr_in = sizeof(struct sockaddr_in);

    memset((void*)&server, 0, size_sockaddr_in);
    memset((void*)&client, 0, size_sockaddr_in);

    fd_socket_server = socket(AF_INET, SOCK_DGRAM, 0);

    if(fd_socket_server == -1){
        handler_error("socket");
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if(bind(fd_socket_server,(struct sockaddr*)&server, size_sockaddr_in) == -1){
        handler_error("bind");
    }

    int my_queue_id = msgget(IPC_PRIVATE, MODE_OPEN);

    if(my_queue_id == -1){
        close(fd_socket_server);
        handler_error("msgget");
    }

    for(int i = 0; i < SIZE_POOL; i++){
        if(pthread_create(&mass_threads[i], NULL, ThreadClient, (void*)&my_queue_id) == -1){
            close(fd_socket_server);
            handler_error("pthread_create");
        }
        pthread_detach(mass_threads[i]);

    }
    
    struct message msgpth;
    socklen_t get_len = 0;

    while(1){
        get_len = size_sockaddr_in;
        
        recvfrom(fd_socket_server, (void*)str_name, SIZE_CLIENT_NAME, 0, (struct sockaddr*)&client, &get_len);
        printf("Server: name: %s %d\n", str_name, fd_socket_server);
        msgpth.message_type = 123;
        strncpy(msgpth.message_text.name_client, str_name, SIZE_CLIENT_NAME);
        msgpth.message_text.socket_server = fd_socket_server;
        memcpy((void*)&msgpth.message_text.client, (void*)&client, size_sockaddr_in);
        msgsnd(my_queue_id, (void*)&msgpth, sizeof(struct message), 0);
        printf("Server: Free threads: %u\n", free_threads);
    }

    close(fd_socket_server);
    return 0;
}