#include "message.h"

#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <errno.h>
#include <string.h>

#include <sys/msg.h>

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