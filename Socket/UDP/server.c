#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <time.h>

#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)


int Server(void);
int GetTime(char *str_time);

int main(void){
    Server();
}

int Server(void){

    char str_time[40] = {0};
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
    serv.sin_port = htons(7777);
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
    
    printf("recv: %s\n", str_recv);
    GetTime(str_time);
    printf("get from port %hd addr %u\n", ntohs(client.sin_port), ntohl(client.sin_addr.s_addr));
    
    sendto(fd_socket, (void*)str_time, 40, 0,(struct sockaddr*)&client, sizeof(struct sockaddr_in));

    close(fd_socket);

    return EXIT_SUCCESS;
}

int GetTime(char *str_time){
    long int ttime;
    ttime = time(NULL);
    strncpy(str_time, ctime(&ttime), 40);
    return 0;
}