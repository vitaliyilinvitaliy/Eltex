#include "udp.h"
#include "ip.h"
#include "../config.h"

#include <stdlib.h>
#include <malloc.h>
#include <string.h>

int CreatePacket(char *packet, char *payload, size_t payload_length){

    char *udp = NULL;
    char *ip = NULL;

    udp = (char*)malloc(UDP_SIZEOF);

    if(udp == NULL){
        handle_error("malloc");
    }

    ip = (char*)malloc(IP_SIZEOF);

    if(ip == NULL){
        handle_error("malloc");
    }

    if(FillUdpHeader(udp, payload_length) == -1){
        handle_error("FillUdpHeader");
    }

    if(FillIpHeader(ip, payload_length) == -1){
        handle_error("FillIpHeader");
    }

    memcpy(packet, ip, IP_SIZEOF);
    memcpy(packet + IP_SIZEOF, udp, UDP_SIZEOF);
    memcpy(packet + UDP_SIZEOF + IP_SIZEOF, payload, payload_length);

    free(ip);
    free(udp);

    return IP_SIZEOF + UDP_SIZEOF + payload_length;
}