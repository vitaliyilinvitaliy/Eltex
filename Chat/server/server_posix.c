#include "../message/message.h"
#include "../message/message.h"

#include <sys/stat.h>
#include <mqueue.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define SERVER_NAME "/server"

struct client{
    mqd_t client_queue_id;
    char client_name[20];
    struct mq_attr client_attr;
};

int main(void){
    char message_online[256] = {0};
    char message[256] = {0};
    unsigned int message_priority = -1;

    int receive_stat = -1;
    int send_stat = -1;
    
    size_t count_client = 0;
    struct client mass_client[10];

    struct mq_attr server_attr;
    server_attr.mq_flags = 0;
    server_attr.mq_maxmsg = 10;
    server_attr.mq_msgsize = 256;
    server_attr.mq_curmsgs = 0;

    mqd_t server_queue = mq_open(SERVER_NAME, O_CREAT|O_RDWR|O_NONBLOCK, MODE, &server_attr);

    if(server_queue == -1){
        perror("open server");
        exit(EXIT_FAILURE);
    }

    while(count_client < 10){
        receive_stat = mq_receive(server_queue, message, 256, &message_priority);

        switch (message_priority)
        {
        case PRIORITY_ONLINE:
            strncpy(mass_client[count_client].client_name, message, 20);

            mass_client[count_client].client_attr.mq_flags = 0;
            mass_client[count_client].client_attr.mq_maxmsg = 10;
            mass_client[count_client].client_attr.mq_msgsize = 256;
            mass_client[count_client].client_attr.mq_curmsgs = 0;

            printf("%s - Online\n", mass_client[count_client].client_name);

            mass_client[count_client].client_queue_id = mq_open(mass_client[count_client].client_name, O_RDWR, 00644, &mass_client[count_client].client_attr);
            
            if(mass_client[count_client].client_queue_id == -1){
                perror("open client");
                exit(EXIT_SUCCESS);
            }

            count_client++;

            strncat(message_online, mass_client[count_client - 1].client_name, 20);
            strncat(message_online, "\n", 1);

            printf("All online:\n%s\n", message_online);

            for(int i = 0; i < count_client; i++){
                send_stat = mq_send(mass_client[i].client_queue_id, message_online, strlen(message_online), PRIORITY_ONLINE);

                if(send_stat == -1){
                    printf("client number %d - name %s\n",i ,mass_client[i].client_name);
                    perror("send online list");
                    exit(EXIT_FAILURE);
                }
            }
            printf("Send online list - success!\n");    
            break;
        
        case PRIORITY_MESSAGE:
            printf("Client %s\n", message);

            for(int i = 0; i < count_client; i++){
                send_stat = mq_send(mass_client[i].client_queue_id, message, strlen(message), PRIORITY_MESSAGE);

                if(send_stat == -1){
                    printf("client number %d - name %s\n",i ,mass_client[i].client_name);
                    perror("send broadcast");
                    exit(EXIT_FAILURE);
                }
            }

            printf("Broadcast - success\n");
            break;

        default:
            break;
        }

        message_priority = -1;
    }

    return EXIT_SUCCESS;

}