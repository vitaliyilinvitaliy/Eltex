#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)


int Client(void);

int main(void){
    Client();
}

int Client(void){
    char str_time[40] = {0};
    char str_send[40] = "Hello";

    struct sockaddr_in server;

    memset(&server, 0, sizeof(server));

    int fd_socket = -1;

    if((fd_socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
        handle_error("socket");
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(7777);
    server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if(connect(fd_socket, (struct sockaddr*)&server, sizeof(server)) == -1){
        close(fd_socket);
        handle_error("connect");
    }

    send(fd_socket, str_send, 40, 0);
    recv(fd_socket, str_time, 40, 0);

    printf("Time: %s\n", str_time);

    close(fd_socket);

    return EXIT_SUCCESS;
}