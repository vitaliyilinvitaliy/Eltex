#include "config.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <time.h>


int Server(void);

int main(void){
    Server();
}

int Server(void){

    char str_recv[40] = {0};

    struct sockaddr_in serv, client;
    int fd_socket = -1, fd_client_socket = -1;

    fd_socket = socket(AF_INET, SOCK_DGRAM, 0);
    /*
    SOCK_DGRAM. Передача данных в виде отдельных сообщений (датаграмм). 
    Предварительная установка соединения не требуется. Обмен данными происходит быстрее, 
    но является ненадёжным: сообщения могут теряться в пути, дублироваться и переупорядочиваться. 
    Допускается передача сообщения нескольким получателям (multicasting) 
    и широковещательная передача (broadcasting).
    */

    if(fd_socket == -1)
        handle_error("socket serv");

    memset(&serv, 0, sizeof(serv));
    memset(&client, 0, sizeof(client));

    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT_SERVER);
    serv.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    /*
    INADDR_LOOPBACK - адрес интерфейса внутренней петли (loopback interface)
    Пакеты, направляемые по этому адресу в сеть не попадут. 
    Вместо этого они передаются стеку протоколов TCP/IP как только что принятые.
    Таким образом моделируется наличие виртуальной сети.
    */

    if(bind(fd_socket, (struct sockaddr*)&serv, sizeof(serv)) == -1){
        close(fd_socket);
        handle_error("bind");
    }

    socklen_t len_client = sizeof(struct sockaddr_in);

    recvfrom(fd_socket, (void*)str_recv, 40, 0, (struct sockaddr*)&client, &len_client);
    printf("str recv = %s\n",str_recv);
    
    for(int i = 0; i < strlen(str_recv); i++){
        if(i % 2 == 0) str_recv[i] = '@';
    }
    
    sendto(fd_socket, (void*)str_recv, 40, 0,(struct sockaddr*)&client, sizeof(struct sockaddr_in));

    close(fd_socket);

    return EXIT_SUCCESS;
}
