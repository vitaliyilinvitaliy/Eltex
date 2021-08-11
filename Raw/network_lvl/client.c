#include "../config.h"
#include "packet.h"
#include "udp.h"
#include "ip.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//gcc client.c udp.c ip.c packet.c -o client

int Client(void);

int main(void){
    return Client();
}

int Client(void){
    int fd_socket = -1;

    fd_socket = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);

    if(fd_socket == -1){
        handle_error("socket");
    }

    int val = 1;

    if(setsockopt(fd_socket, IPPROTO_IP, IP_HDRINCL, (void*)&val, sizeof(val)) == -1){
        close(fd_socket);
        handle_error("setsockopt");
    }
    /*
    Уровень IPv4 генерирует заголовок IP при посылке пакета, 
    если только для сокета не включён параметр IP_HDRINCL. 
    Если он включён, то пакет должен содержать заголовок IP. 
    Принимаемые пакеты всегда содержат заголовок IP.
    */

    struct sockaddr_in server;
    memset((void*)&server, 0, sizeof(struct sockaddr_in));

    server.sin_family = AF_INET;
    server.sin_port = htons(7777);
    server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    char *packet = NULL;

    packet = (char*)malloc(IP_SIZEOF + UDP_SIZEOF + 7);

    if(packet == NULL){
        handle_error("malloc");
    }

    char payload[7] = "Hello!";

    int packet_len = CreatePacket(packet, payload, 7);    

    if(packet_len == -1){
        handle_error("CreatePacket");
    }

    socklen_t sockl = sizeof(struct sockaddr_in);

    sendto(fd_socket, (void*)packet, packet_len, 0, (struct sockaddr*)&server, sockl);

    char *ptr = NULL;
    char recv_str[7] = {0};
    char recv_pack[IP_SIZEOF + UDP_SIZEOF + 7] = {0};
    int break_flag = 0;

    while(1){
        break_flag = 0;
        recvfrom(fd_socket, (void*)recv_pack, IP_SIZEOF + UDP_SIZEOF + 7, 0, NULL, NULL);
        ptr = recv_pack + 28;//20 байт заголовок ip 8 udp, остальное нужная нам строка
        memcpy((void*)recv_str, (void*)ptr, 7);
        printf("str: %s\n", recv_str);
        
        for(int i = 0; i < strlen(recv_str); i++){
            if(i % 2 == 0 && recv_str[i] == '@') break_flag++;
        }

        if(break_flag == 3) break;
    }

    free(packet);

    return 0;
}