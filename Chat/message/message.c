#include "message.h"

#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

#include <mqueue.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdlib.h>

int CreateQueueSystemV(struct parameters_system_v *params){
    key_t server_queue_key;
    int server_queue_id;
    int my_queue_id;

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

    return 0;
}

int CreateQueuePOSIX(char *user_name,struct parameters_POSIX *params){
    struct mq_attr my_attr;

    my_attr.mq_flags = 0;
    my_attr.mq_maxmsg = 10;
    my_attr.mq_msgsize = 256;
    my_attr.mq_curmsgs = 0;

    struct mq_attr server_attr;

    server_attr.mq_flags = 0;
    server_attr.mq_maxmsg = 10;
    server_attr.mq_msgsize = 256;
    server_attr.mq_curmsgs = 0;

    mqd_t my_queue_id = mq_open(user_name, O_CREAT|O_RDWR, MODE, &my_attr);

    if(my_queue_id == -1){
        perror("my open");
        exit(EXIT_FAILURE);
    }

    mqd_t server_queue_id = mq_open(SERVER_NAME, O_RDWR, &server_attr);

    if(server_queue_id == -1){
        perror("server open");
        exit(EXIT_FAILURE);
    }

    (*params).my_queue_id = my_queue_id;
    (*params).server_queue_id = server_queue_id;

    return 0;
}

