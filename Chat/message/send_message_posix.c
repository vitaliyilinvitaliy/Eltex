#include "message.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int SendMessagePOSIX(char *message, struct my_parameters my_par){
    struct parameters_POSIX *par_posix = (struct parameters_POSIX *)my_par.parameters_queue;

    char send_mess[256] = {0};

    strncpy(send_mess,my_par.name,256);
    size_t len_text = strlen(send_mess);
    strncat(send_mess, ": ", (256 - len_text));
    len_text = strlen(send_mess);
    strncat(send_mess, message, (256 - len_text));

    int stat_send = mq_send((*par_posix).server_queue_id, send_mess, strlen(send_mess), PRIORITY_MESSAGE);

    if(stat_send == -1){
        perror("send message");
        exit(EXIT_FAILURE);
    }
}