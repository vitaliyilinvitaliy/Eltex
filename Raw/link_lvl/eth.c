#include "eth.h"

#include <string.h>
#include <arpa/inet.h>

char destination_mac[6] = {0x02, 0x42, 0xac, 0x11, 0x00, 0x03}; 
char source_mac[6] = {0x02, 0x42, 0xfc, 0x12, 0x0d, 0x63};

int FillEthHeader(char *eth_header){
    memcpy(eth_header, destination_mac, MAC_SIZEOF);
    memcpy(eth_header + MAC_SIZEOF, source_mac, MAC_SIZEOF);
    
    int tag_protocol_identifier = htons(0x8100);
    //Для 802.1Q используется значение 0x8100
    memcpy(eth_header + (2 * MAC_SIZEOF), &tag_protocol_identifier, TPI);
    short type = htons(0x0800);
    /*
    0x0800 - указывает что на сетевом уровне используется 
    четвёртая версия интернет-протокола (IP)
    */
    memcpy(eth_header + (2 * MAC_SIZEOF) + TPI, &type, 2);

    return 0;
}