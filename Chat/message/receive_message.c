#include "message.h"

#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>

#include <fcntl.h>
#include <mqueue.h>
#include <sys/stat.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>


void *ReceiveMessageSystemV(void *args){
    int my_queue_id = -1;
    int snd_stat = -1;
    int rec_stat = -1;

    int pos_y_chat = 1;
    int pos_y_online = 1;

    struct my_parameters *my_param = (struct my_parameters *) args;
    struct parameters_system_v *queue_param = (struct parameters_system_v *) (*my_param).parameters_queue;

    struct message server_message;

    my_queue_id = (*queue_param).my_queue_id;

    if(my_queue_id == -1){
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    strncpy(server_message.message_text.text, (*my_param).name, 20);
    server_message.message_text.text[strlen((*my_param).name)] = '\n';
    server_message.message_type = 2;
    server_message.message_text.queue_id = my_queue_id;

    snd_stat = msgsnd((*queue_param).server_queue_id, &server_message, sizeof(struct message), 0);

    if(snd_stat == -1){
        perror("registration");
        exit(EXIT_FAILURE);
    }

    while(1){
        rec_stat = msgrcv(my_queue_id, &server_message, sizeof(struct message), 0 , 0);
        
        if(rec_stat == -1){
            wmove((*my_param).chat, pos_y_chat, 1);
            pos_y_chat++;
            perror("rec");
            break;
        }

        if(server_message.message_type == 3){
            for(int i = 0, x_str = 1; i < strlen(server_message.message_text.text); i++, x_str++){
                mvwaddch((*my_param).online, pos_y_online, x_str, server_message.message_text.text[i]);
                if(x_str == 20 || server_message.message_text.text[i] == '\n'){
                    x_str = 0;
                    pos_y_online++;
                }
            }
            pos_y_online = 1;
            wrefresh((*my_param).online);
        }else{
            for(int i = 0; i < strlen(server_message.message_text.text); i++){
                mvwaddch((*my_param).chat, pos_y_chat, i + 1, server_message.message_text.text[i]);
            }
            pos_y_chat++;
            wrefresh((*my_param).chat);
        }

    }
}

void *ReceiveMessagePOSIX(void *args){
    char message[256] = {0};
    
    int my_queue_id = -1;
    int snd_stat = -1;
    int rec_stat = -1;

    int pos_y_chat = 1;
    int pos_y_online = 1;

    unsigned int priority_message = -1;

    struct my_parameters *my_param = (struct my_parameters *) args;
    struct parameters_POSIX *queue_param = (struct parameters_POSIX *) (*my_param).parameters_queue;

    my_queue_id = (*queue_param).my_queue_id;

    if(my_queue_id == -1){
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    strncpy(message, (*my_param).name, 20);
    message[strlen((*my_param).name)] = '\n';
    
    snd_stat = mq_send((*queue_param).server_queue_id, message, strlen(message), PRIORITY_ONLINE);

    if(snd_stat == -1){
        perror("send online");
        exit(EXIT_FAILURE);
    }

    while(1){
        rec_stat = mq_receive((*queue_param).my_queue_id, message, 256, &priority_message);
        
        if(rec_stat == -1){
            wmove((*my_param).chat, pos_y_chat, 1);
            pos_y_chat++;
            perror("rec");
            break;
        }

        if(priority_message == PRIORITY_ONLINE){
            for(int i = 0, x_str = 1; i < strlen(message); i++, x_str++){
                mvwaddch((*my_param).online, pos_y_online, x_str, message[i]);
                if(x_str == 20 || message[i] == '\n'){
                    x_str = 0;
                    pos_y_online++;
                }
            }
            pos_y_online = 1;
            wrefresh((*my_param).online);
        }else{
            for(int i = 0; i < strlen(message); i++){
                mvwaddch((*my_param).chat, pos_y_chat, i + 1, message[i]);
            }
            pos_y_chat++;
            wrefresh((*my_param).chat);
        }

    }
}
