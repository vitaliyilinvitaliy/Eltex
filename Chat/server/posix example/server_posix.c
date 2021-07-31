#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define SERVER_NAME "/server"
#define MODE 00644
#define PRIORITY_ONLINE 1
#define PRIORITY_MESSAGE 2

//cat /dev/mqueue/server

int main(){
    int stat_receive = -1;
    int stat_send = -1;
    int priority_message = -1;
    
    char receive_message[256] = {0};
    char send_message[256] = {0};

    mqd_t queue_client = -1;

    struct mq_attr server_attr;
    server_attr.mq_flags = 0;
    server_attr.mq_maxmsg = 10;
    server_attr.mq_msgsize = 256;
    server_attr.mq_curmsgs = 0; 

    struct mq_attr client_attr;
    server_attr.mq_flags = 0;
    server_attr.mq_maxmsg = 10;
    server_attr.mq_msgsize = 256;
    server_attr.mq_curmsgs = 0; 

    mqd_t queue_server = mq_open(SERVER_NAME, O_CREAT|O_RDWR, 00644, &server_attr);

    if(queue_server == -1){
        perror("open server");
        exit(EXIT_FAILURE);
    }

    printf("Start server\n");

    while(1){
        stat_receive = mq_receive(queue_server, receive_message, 256, &priority_message);

        if(stat_receive == -1){
            perror("receive");
            exit(EXIT_FAILURE);
        }

        switch (priority_message)
        {
        case PRIORITY_ONLINE:
            queue_client = mq_open(receive_message, O_RDWR, 00644, &client_attr);

            if(queue_client == -1){
                perror("open client");
                exit(EXIT_FAILURE);
            }

            printf("Client %s - online\n",receive_message);
            break;
        
        case PRIORITY_MESSAGE:
            printf("New message: %s\n", receive_message);
            break;

        default:
            break;
        }

        
    }

    

    return EXIT_SUCCESS;
}