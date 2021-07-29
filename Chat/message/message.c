#include "message.h"

#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <stdlib.h>

int GetParamsMessage(struct my_parameters *params){
    key_t server_queue_key;
    int server_queue_id;
    int my_queue_id;

    struct message my_message;
    struct message server_message;

    int send_stat = 0;
    int ctl_stat = 0;

    my_queue_id = msgget(IPC_PRIVATE, QUEUE_PERMISSIONS);

    if(my_queue_id == -1){
        perror("my q id");
        exit(EXIT_FAILURE);
    }

    server_queue_key = ftok(PATH_QUEUE, PROJECT_ID);

    if(server_queue_key == -1){
        perror("serv q key");
        exit(EXIT_FAILURE);
    } 

    server_queue_id = msgget(server_queue_key, 0);

    if(server_queue_id == -1){
        perror("serv q key");
        exit(EXIT_FAILURE);
    }

    (*params).server_queue_id = server_queue_id;
    (*params).server_queue_key = server_queue_key;
    (*params).my_queue_id = my_queue_id;
}
