#ifndef _UDP_H_
#define _UDP_H_

#define UDP_SIZEOF 8

#define SOURCE_PORT_OFFSET 0
#define DESTINATION_PORT_OFFSET 2
#define UDP_LENGTH_OFFSET 4
#define UDP_CHECKSUM_OFFSET 6
#define UDP_PAYLOAD_OFFSET 8


int FillUdpHeader(char *, unsigned short);

#endif //_UDP_H_