#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <sys/ipc.h>
#include <ncurses.h>

#define PATH_QUEUE "./queue.txt"
#define PROJECT_ID 'A'
#define QUEUE_PERMISSIONS 0660

struct message_text{
    int queue_id;
    char text[256];
};

struct message{
    long message_type;
    struct message_text message_text;
};


struct my_parameters{
    key_t server_queue_key;
    int server_queue_id;
    int my_queue_id;
    WINDOW *chat;
    WINDOW *online;
    char name[20];
};

int GetParamsMessage(struct my_parameters *params);

#endif //_MESSAGE_H_