#ifndef _CONFIG_H_
#define _CONFIG_H_

/*#define UDP_SIZEOF 8

#define SOURCE_PORT_OFFSET 0
#define DESTINATION_PORT_OFFSET 2
#define LENGTH_OFFSET 4
#define CHECKSUM_OFFSET 6
#define DESTINATION_OFFSET 8
*/
#define PORT_SERVER 7777
#define PORT_CLIENT 8888


#define handle_error(msg) do{\
perror(msg);\
return 1;}while(0)

#endif //_CONFIG_H_