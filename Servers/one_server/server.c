#include "../handler_error.h"
#include "../config.h"
#include "../time/time.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

//gcc ./one_server/server.c ./time/time.c -o serv_one

int ServerNtp(void);

int main(void){
    return ServerNtp();
}

int ServerNtp(void){
    int fd_serv_socket = -1;
    int counter_client = 0;
    struct sockaddr_in server, client;

    char str_time[SIZE_STR_TIME] = {0};
    char str_client_name[SIZE_CLIENT_NAME] = {0};
    char send_message[SIZE_SEND_MESSAGE] = {0};

    socklen_t size_sockaddr_in = sizeof(struct sockaddr_in);

    fd_serv_socket = socket(AF_INET, SOCK_DGRAM, 0);

    if(fd_serv_socket == -1){
        handler_error("socket");
    }

    memset((void*)&server, 0, size_sockaddr_in);
    memset((void*)&client, 0, size_sockaddr_in);
    
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if(bind(fd_serv_socket, (struct sockaddr*)&server, size_sockaddr_in) == -1){
        close(fd_serv_socket);
        handler_error("bind");
    }

    socklen_t get_size = 0;

    while(counter_client < MAX_CLIETNS)
    {
        get_size = size_sockaddr_in;

        recvfrom(fd_serv_socket, (void*)str_client_name, SIZE_CLIENT_NAME, 0, (struct sockaddr*)&client, &get_size);
        
        sleep(10);//имитация деятельности

        strncat(send_message, "Hi, ", SIZE_SEND_MESSAGE);
        strncat(send_message, str_client_name, SIZE_SEND_MESSAGE);
        strncat(send_message, " current time: ", SIZE_SEND_MESSAGE);

        GetTime(str_time);

        strncat(send_message, str_time, SIZE_SEND_MESSAGE);

        sendto(fd_serv_socket, send_message, SIZE_SEND_MESSAGE, 0, (struct sockaddr*)&client, get_size);

        printf("%d Client %s\n", counter_client, str_client_name);
        memset((void*)str_client_name, 0, SIZE_CLIENT_NAME);
        memset((void*)&client, 0, size_sockaddr_in);
        memset((void*)&send_message, 0, size_sockaddr_in);

        counter_client++;
    }

}