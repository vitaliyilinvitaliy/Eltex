#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define handler_error(str) do{\
    perror(str);\
    return 1;}while(0)

int Sender(void);

int main(){
    return Sender();
}

int Sender(void){
    int fd_socket = -1;
    char str_send[10] = "Broadcast";

    fd_socket = socket(AF_INET, SOCK_DGRAM, 0);

    if(fd_socket == -1){
        handler_error("Socket");
    }

    struct sockaddr_in endpoint;
    memset((void*)&endpoint, 0, sizeof(struct sockaddr_in));

    endpoint.sin_family = AF_INET;
    endpoint.sin_port = htons(7777);
    
    struct in_addr addr;

    inet_aton("224.0.0.1", &addr);

    endpoint.sin_addr = addr;

    printf("send:\n");
    ssize_t send_size = -1;
    send_size = sendto(fd_socket, str_send, strlen(str_send), 0, (struct sockaddr*)&endpoint, sizeof(endpoint));

    printf("send = %ld\n", send_size);

    if(send_size == -1){
        close(fd_socket);
        handler_error("sendto");
    }

    close(fd_socket);
    return 0;
}