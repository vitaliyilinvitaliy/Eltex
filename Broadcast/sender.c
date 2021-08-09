/*
    Broadcast
*/

#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define handler_error(str) do{\
    perror(str);\
    return 1;}while(0)


int Sender(void);

int main(void){
    return Sender();
}

int Sender(void){
    int fd_socket = -1;
    fd_socket = socket(AF_INET, SOCK_DGRAM, 0);

    const char str_brc[10] = "broadcast";

    if(fd_socket == -1){
        handler_error("socket");
    }

    int val = 1;
    socklen_t size_val = sizeof(val);

    if(setsockopt(fd_socket, SOL_SOCKET, SO_BROADCAST, &val, size_val) == - 1){
        close(fd_socket);
        handler_error("setsockopt");
    }
    /*
    SOL_SOCKET - уровень бибилиотеки сокетов

    SO_BROADCAST - Задать или считать флаг широкого вещания. 
    Если он установлен, то датаграммные сокеты принимают пакеты, 
    отправленные по широковещательному адресу, и могут сами посылать пакеты 
    по этому адресу. Эта опция не воздействует на сокеты, ориентированные на потоки.
    */
    struct sockaddr_in broadcast;

    memset((void*)&broadcast, 0, sizeof(struct sockaddr_in));

    broadcast.sin_family = AF_INET;
    broadcast.sin_port = htons(7777);
    
    struct in_addr address_br;
    inet_aton("255.255.255.255", &address_br);

    broadcast.sin_addr = address_br;

    ssize_t send_ssize = 0;
    socklen_t len = sizeof(struct sockaddr_in);

    printf("send:\n");

    send_ssize = sendto(fd_socket, (void*)str_brc, strlen(str_brc), 0,(struct sockaddr*) &broadcast, len);
    if(send_ssize == -1){
        close(fd_socket);
        handler_error("sendto");
    }

    printf("size = %ld\n", send_ssize);
    close(fd_socket);

    return 0;
}