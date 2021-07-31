#include <sys/stat.h>
#include <mqueue.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/*
mq_open Открытие/создание очереди сообщений.
mq_close Закрытие очереди сообщений.
mq_getattr Получение атрибутов очереди сообщений.
mq_setattr Установка атрибутов очереди сообщений.
mq_send Отправка сообщения в очередь.
mq_receive Приём сообщения из очереди.
mq_timedsend Отправка сообщения в очередь. Блокируется в течение заданного времени.
mq_timedreceive Приём сообщения из очереди. Блокируется в течение заданного времени.
mq_notify Регистрация для получения уведомления всякий раз, когда получено сообщение в пустой очереди сообщений.
mq_unlink Удаление очереди сообщений.
*/

#define SERVER_NAME "/server"
#define MODE 00644
#define PRIORITY_REGISTRATION 1

int main(){
    char client_name[20] = {0};
    char message[256] = {0};

    unsigned int priority_message = 0;
    int stat_receive = 0;

    printf("Enter your name: \n");
    scanf("%s", client_name);

    struct mq_attr client_attr;
    client_attr.mq_flags = 0;
    client_attr.mq_maxmsg = 10; //Максимальное количество сообщений, которые могут храниться в очереди. 
    client_attr.mq_msgsize = 256; //Максимальный размер каждого сообщения в данной очереди сообщений.
    client_attr.mq_curmsgs = 0; //Количество сообщений, находящихся в данный момент в данной очереди.

    struct mq_attr server_attr;
    client_attr.mq_flags = 0;
    client_attr.mq_maxmsg = 10; //Максимальное количество сообщений, которые могут храниться в очереди. 
    client_attr.mq_msgsize = 256; //Максимальный размер каждого сообщения в данной очереди сообщений.
    client_attr.mq_curmsgs = 0; //Количество сообщений, находящихся в данный момент в данной очереди.

    mqd_t queue_server = mq_open(SERVER_NAME, O_RDWR, MODE, &server_attr);

    if(queue_server == -1){
        perror("open server");
        exit(EXIT_FAILURE);
    }

    mqd_t queue_client = mq_open(client_name, O_CREAT|O_RDWR, MODE, &client_attr);

    if(queue_client == -1){
        perror("open client");
        exit(EXIT_FAILURE);
    }

    /*printf("Enter message: \n");
    scanf("%s");*/

    

    stat_receive = mq_send(queue_server, client_name, strlen(client_name), PRIORITY_REGISTRATION);

    if(stat_receive == -1){
        perror("send");
    }

    return EXIT_SUCCESS;
}