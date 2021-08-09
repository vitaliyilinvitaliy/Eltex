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
#include <string.h>

#include <arpa/inet.h>//inet_aton

#define handler_error(str) do{\
    perror(str);\
    return 1;}while(0)

int Receiver(void);

int main(void){
    return Receiver();
}

int Receiver(void){
    int fd_socket = -1;
    char str_recv[20] = {0};
    socklen_t size_addr_in = sizeof(struct sockaddr_in);

    fd_socket = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in addr;

    memset((void*)&addr, 0, size_addr_in);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(7777);
    
    struct in_addr address_br;

    inet_aton("255.255.255.255", &address_br);
    /*
    inet_aton() преобразовывает обычный вид IP-адреса cp (из номеров и точек) 
    в двоичный код и сохраняет его в структуре
    255.255.255.255 - универсальный широковещательный адрес
    */
    addr.sin_addr = address_br;

    if(bind(fd_socket, (struct sockaddr*)&addr, size_addr_in) == -1){
        close(fd_socket);
        handler_error("bind");
    }

    printf("recv:\n");
    recvfrom(fd_socket, (void*)str_recv, 20, 0, NULL, NULL);
    
    close(fd_socket);
    
    return 0;
}