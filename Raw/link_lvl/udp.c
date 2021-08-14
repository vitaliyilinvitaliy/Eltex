#include "../config.h"
#include "udp.h"

#include <malloc.h>
#include <string.h> 
#include <netinet/in.h>


int FillUdpHeader(char *udp, unsigned short payload_len){
    
    size_t short_sizeof = sizeof(short);

    memset((void*)udp, 0, UDP_SIZEOF);

    short n_port_source = htons(PORT_CLIENT);
    short n_port_destination = htons(PORT_SERVER);
    short n_length = htons(payload_len + UDP_SIZEOF);
    short n_check_sum = htons(0);

    memcpy((void*)udp + SOURCE_PORT_OFFSET, (void*)&n_port_source, short_sizeof);
    memcpy((void*)udp + DESTINATION_PORT_OFFSET, (void*)&n_port_destination, short_sizeof);
    memcpy((void*)udp + UDP_LENGTH_OFFSET, (void*)&n_length, short_sizeof);
    memcpy((void*)udp + UDP_CHECKSUM_OFFSET, (void*)&n_check_sum, short_sizeof);

    return 0;
}