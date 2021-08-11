#include "../config.h"
#include "network_lvl/udp.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/ip.h>//IPPROTO_UDP
#include <malloc.h>
#include <string.h>
#include <netinet/in.h>

int Client(void);

int main(void){
    return Client();
}

int Client(void){
    int fd_socket = -1;
    char *buf = NULL;
    char *head = NULL;
    char str_hello[7] = "hello!";

    char recv_pack[100] = {0};
    
    fd_socket = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);

    if(fd_socket == -1){
        handle_error("socket");
    }

    short source_port = htons(PORT_CLIENT);
    short destination_port = htons(PORT_SERVER);
    short length_pack = htons(UDP_SIZEOF + 7);
    short check_sum = htons(0);

    buf = (char*) malloc(UDP_SIZEOF + 7);//7 - payload 

    if(buf == NULL){
        close(fd_socket);
        handle_error("malloc");
    }

    memcpy((void*)buf + SOURCE_PORT_OFFSET, &source_port, sizeof(short));
    memcpy((void*)buf +  DESTINATION_PORT_OFFSET, &destination_port, sizeof(short));
    memcpy((void*)buf + UDP_LENGTH_OFFSET, &length_pack, sizeof(short));
    memcpy((void*)buf + UDP_CHECKSUM_OFFSET, &check_sum, sizeof(short));
    memcpy((void*)buf + UDP_PAYLOAD_OFFSET, str_hello, 7);

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT_SERVER);
    server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    ssize_t size_sendto = 0;

    size_sendto = sendto(fd_socket, buf, UDP_SIZEOF + 7, 0, (struct sockaddr*)&server, sizeof(struct sockaddr_in));

    if(size_sendto == -1){
        close(fd_socket);
        handle_error("sendto");
    }

    char *ptr = NULL;
    char recv_str[7] = {0};
    int break_flag = 0;

    while(1){
        break_flag = 0;
        recvfrom(fd_socket, (void*)recv_pack, 100, 0, NULL, NULL);
        ptr = recv_pack + 28;//20 байт заголовок ip 8 udp, остальное нужная нам строка
        memcpy((void*)recv_str, (void*)ptr, 7);
        printf("str: %s\n", recv_str);
        
        for(int i = 0; i < strlen(recv_str); i++){
            if(i % 2 == 0 && recv_str[i] == '@') break_flag++;
        }

        if(break_flag == 3) break;
    }

    free(buf);
    close(fd_socket);
    return 0;
}
