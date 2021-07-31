#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <sys/ipc.h>
#include <ncurses.h>
#include <mqueue.h>

//System V 
#define PATH_QUEUE "./queue.txt"
#define PROJECT_ID 'A'
#define QUEUE_PERMISSIONS 0660

//POSIX
#define SERVER_NAME "/server"
#define MODE 00644
#define PRIORITY_ONLINE 1
#define PRIORITY_MESSAGE 2

//POSIX
struct parameters_POSIX{
    mqd_t server_queue_id;
    mqd_t my_queue_id;
};

//System V 
struct message_text{
    int queue_id;
    char text[256];
};
//System V 
struct message{
    long message_type;
    struct message_text message_text;
};

//System V 
struct parameters_system_v{
    key_t server_queue_key;
    int server_queue_id;
    int my_queue_id;
};

//Общее
struct my_parameters{
    WINDOW *chat;
    WINDOW *online;
    char name[20];
    void *parameters_queue;
};

//System V 
int CreateQueueSystemV(struct parameters_system_v *);
//POSIX
int CreateQueuePOSIX(char *user_name,struct parameters_POSIX *params);

#endif //_MESSAGE_H_