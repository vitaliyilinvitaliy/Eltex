#include <sys/types.h>

#include <sys/socket.h>
#include <sys/un.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <unistd.h>

#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)


int Client(void);

int main(void){
    return Client();
}

int Client(void){
    char str_time[40] = {0};
    
    struct sockaddr_un addr_serv;

    int fd_socket = socket(AF_LOCAL, SOCK_STREAM, 0);

    memset(&addr_serv, 0, sizeof(struct sockaddr_un));

    addr_serv.sun_family = AF_LOCAL;
    strncpy(addr_serv.sun_path, "/tmp/stream_serv1", sizeof(addr_serv.sun_path) - 1);

    if(connect(fd_socket, (struct sockaddr*) &addr_serv, sizeof(struct sockaddr_un)) == -1)
        handle_error("connect");

    recv(fd_socket, (void *)str_time, 40, 0);

    printf("Time: %s\n", str_time);

    close(fd_socket);
}