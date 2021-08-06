#include <sys/types.h>

#include <sys/socket.h>//socket(); bind();
#include <sys/un.h>//sockaddr_un

#include <unistd.h>//close();

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>

#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)


int Server(void);
int GetTime(char *str_time);

int main(void){
    return  Server();
}

int Server(void){
    char str_time[40] = {0};

    /*sockaddr_XX (XX - суффикс, обозначающий домен: "un" - Unix, "in" - Internet и т. д.).*/
    struct sockaddr_un addr, client_addr;

    /*fd_socket - дескриптор сокета через который принимаем данные*/
    int fd_socket = -1;
    int fd_client_socket = -1;
    
    /*
    1)  AF_LOCAL     Synonym for AF_UNIX.
        AF_UNIX      Local communication.
        При задании AF_UNIX для передачи данных используется файловая система ввода/вывода Unix. 
    2)  SOCK_STREAM. Передача потока данных с предварительной установкой соединения (TCP).
    3)  0 - семейство адресов по умолчанию. 
    */
    if((fd_socket = socket(AF_LOCAL, SOCK_STREAM, 0)) == -1) 
        handle_error("socket");
   
    /*clear structure*/
    memset(&addr, 0, sizeof(struct sockaddr_un));
    memset(&client_addr, 0, sizeof(struct sockaddr_un));

    addr.sun_family = AF_LOCAL;
    strncpy(addr.sun_path, "/tmp/stream_serv1", sizeof(addr.sun_path) - 1);

    /*Для явного связывания сокета с некоторым адресом используется функция bind*/
    if(bind(fd_socket, (struct sockaddr*) &addr, sizeof(struct sockaddr_un)) == -1) 
        handle_error("bind");

    /*Cокет переводится в режим ожидания запросов со стороны клиентов.*/
    if(listen(fd_socket, 5) == -1)
        handle_error("listen");
    
    /*Функция accept создаёт для общения с клиентом новый сокет и возвращает его дескриптор.*/
    socklen_t sockl = 0;

    if((fd_client_socket = accept(fd_socket,(struct sockaddr*) &client_addr, &sockl)) == -1)
        handle_error("accept");

    GetTime(str_time);

    /*Функция send используется для отправки данных */
    if(send(fd_client_socket,(void*) str_time, 40, 0/*флаги не используются*/) == -1);

    close(fd_client_socket);
    close(fd_socket);

    return EXIT_SUCCESS;
}

int GetTime(char *str_time){
    long int ttime;
    ttime = time(NULL);
    strncpy(str_time, ctime(&ttime), 40);
    return 0;
}