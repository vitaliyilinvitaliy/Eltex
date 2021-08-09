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

int Receiver(void);

int main(void){
    return Receiver();
}

int Receiver(void){
    int fd_socket = -1;

    char get_ms[20] = {0};

    fd_socket = socket(AF_INET, SOCK_DGRAM, 0);

    if(fd_socket == -1){
        handler_error("socket");
    }

    struct sockaddr_in sock;

    memset((void*)&sock, 0, sizeof(struct sockaddr_in));

    sock.sin_family = AF_INET;
    sock.sin_port = htons(7777);
    sock.sin_addr.s_addr = htonl(INADDR_ANY);

    socklen_t len_sock = sizeof(sock);

    if(bind(fd_socket, (struct sockaddr*)&sock, len_sock) == -1){
        close(fd_socket);
        handler_error("bind");
    }

    struct ip_mreqn reqn;

    struct in_addr addr;
    inet_aton("224.0.0.1", &addr);

    reqn.imr_multiaddr = addr;
    reqn.imr_address.s_addr = htonl(INADDR_ANY);
    reqn.imr_ifindex = 0;

    if(setsockopt(fd_socket, IPPROTO_IP, IP_ADD_MEMBERSHIP,(void*) &reqn, sizeof(reqn)) == -1){
        close(fd_socket);
        handler_error("setsockopt");
    }

    printf("recv:\n");
    
    ssize_t recv_size = -1;

    while(1){
        recv_size = recvfrom(fd_socket, get_ms, 20, 0, NULL, NULL);
        printf("str: %s %ld\n", get_ms, recv_size);
    }

    return 0;
}