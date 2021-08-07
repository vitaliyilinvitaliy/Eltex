#include "handler_error.h"
#include "config.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>


int NTP(char *, char *);

int main(void){
    char name_client[SIZE_CLIENT_NAME] = {0};
    char str_time[SIZE_STR_TIME] = {0};

    printf("Enter your name: ");
    scanf("%50s", name_client);

    NTP(name_client, str_time);

    printf("Server time: %s", str_time);

    return EXIT_SUCCESS;
}

int NTP(char *name_client, char *str_time){

    int fd_serv_socket = -1;
    struct sockaddr_in server;

    socklen_t size_sockaddr_in = sizeof(struct sockaddr_in);

    fd_serv_socket = socket(AF_INET, SOCK_DGRAM, 0);

    if(fd_serv_socket == -1){
        handler_error("socket");
    }

    memset((void *)&server, 0, size_sockaddr_in);

    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if(connect(fd_serv_socket, (struct sockaddr*)&server, size_sockaddr_in) == -1){
        close(fd_serv_socket);
        handler_error("connect");
    }
    
    send(fd_serv_socket, name_client, SIZE_CLIENT_NAME, 0);
    recv(fd_serv_socket, str_time, SIZE_STR_TIME, 0);

    close(fd_serv_socket);

    return 0;
}