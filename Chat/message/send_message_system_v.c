#include "message.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/msg.h>

int SendMessageSystemV(char *message, struct my_parameters my_par){

    struct parameters_system_v *queue = NULL;
    queue = (struct parameters_system_v *) my_par.parameters_queue; 

    int send_stat = 0;
    int ctl_stat = 0;

    struct message my_message;
    struct message server_message;

    my_message.message_type = 1;
    my_message.message_text.queue_id = (*queue).my_queue_id;
    
    strncpy(my_message.message_text.text,my_par.name,256);
    size_t len_text = strlen(my_message.message_text.text);
    strncat(my_message.message_text.text, ": ", (256 - len_text));
    len_text = strlen(my_message.message_text.text);
    strncat(my_message.message_text.text, message, (256 - len_text));

    len_text = strlen(my_message.message_text.text);

    my_message.message_text.text[len_text] = 0;
    my_message.message_type = 1;

    send_stat = msgsnd((*queue).server_queue_id, &my_message, sizeof(struct message_text),0);

    if(send_stat == -1){
        perror("send");
        exit(EXIT_FAILURE);
    }    

    return 0;
}