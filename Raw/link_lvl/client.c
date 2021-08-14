#include "packet.h"
#include "ip.h"
#include "udp.h"
#include "eth.h"
#include "../config.h"

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <linux/if_ether.h>//ETH_P_ALL
#include <netpacket/packet.h>
#include <string.h>
#include <net/if.h>
#include <unistd.h>

extern char destination_mac[6];
extern char source_mac[6];

int Client(void);

int main(void){
    return Client();
}

int Client(void){

    char str_payload[7] = "Hello!";

    int fd_socket = -1;
    fd_socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    /*
    ETH_P_ALL - программой принимаются все протоколы
    AF_PACKET - для приема датаграмм, содержащих 14-байтовый заголовок Ethernet, 
    за которым следуют некоторые другие заголовки протоколов более высокого уровня
    */

    if(fd_socket == -1){
        handle_error("socket");
    }

    struct sockaddr_ll serv;
    memset((void*)&serv, 0, sizeof(struct sockaddr_ll));

    serv.sll_family = AF_PACKET;
    serv.sll_halen = 6;//размер mac
    serv.sll_ifindex = if_nametoindex("docker0");
    /*
    По умолчанию для контейнеров используется bridge. 
    При первом запуске контейнера Docker создает дефолтную bridge-сеть
    с одноименным названием. Эту сеть можно увидеть в общем списке 
    по команде docker network ls.

    Каждая bridge-сеть имеет свое представление в виде интерфейса на хосте. 
    С сетью “bridge”, которая стоит по умолчанию, 
    обычно ассоциируется интерфейс docker0,
    */
    strncpy(serv.sll_addr,destination_mac,6);

    printf("%u\n", serv.sll_ifindex);

    char *packet = NULL;

    size_t pack_size = ETH_SIZEOF + IP_SIZEOF + UDP_SIZEOF + 7;

    packet = (char*)malloc(pack_size);

    if(packet == NULL){
        handle_error("malloc");
    }

    char payload[7] = "Hello!";

    int packet_len = CreatePacket(packet, payload, 7);    

    if(packet_len == -1){
        handle_error("CreatePacket");
    }  

    int stat_send = -1;

    stat_send = sendto(fd_socket, (void*)packet, packet_len, 0, (struct sockaddr*)&serv, sizeof(struct sockaddr_ll));

    if(stat_send == -1){
        close(fd_socket);
        handle_error("sendto");
    }

    char *ptr = NULL;
    char recv_str[7] = {0};
    char recv_pack[ETH_SIZEOF + IP_SIZEOF + UDP_SIZEOF + 10] = {0};
    int break_flag = 0;

    while(1){
        break_flag = 0;
        recvfrom(fd_socket, (void*)recv_pack,ETH_SIZEOF + IP_SIZEOF + UDP_SIZEOF + 10, 0, NULL, NULL);
        ptr = recv_pack + ETH_SIZEOF + IP_SIZEOF + UDP_SIZEOF - 4;//-4 т.к. принимаем 14 байтную версию Ethernet заголовка
        memcpy((void*)recv_str, (void*)ptr, 7);
        printf("str: %s\n", recv_str);
        
        for(int i = 0; i < strlen(recv_str); i++){
            if(i % 2 == 0 && recv_str[i] == '@') break_flag++;
        }

        if(break_flag == 3) break;
    }

    close(fd_socket);

    return 0;
}
