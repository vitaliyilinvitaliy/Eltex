#include <stdlib.h>

int CheckSum(char *ip_header){
    int csum = 0;
    short *ptr = NULL;

    ptr = (short*)ip_header;

    for(int i = 0; i < 10; i++){
        csum = csum + *ptr;
        ptr++;
    }

    int tmp = csum >> 16; //crc16
    csum = (csum & 0xFFFF) + tmp;
    csum = ~csum;

    return csum;
}