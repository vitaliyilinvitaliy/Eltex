/*
 * server.c: Server program
 *           to demonstrate interprocess commnuication
 *           with System V message queues
 */
#include "../message/message.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


struct client{
    int client_queue_id;
    char client_name[20];
};

int main(int argc, char **argv)
{
    key_t msg_queue_key;
    int qid;
    struct message message;
    struct message message_online;

    size_t count_client = 0;

    /*struct client *mass_client = NULL;

    mass_client = calloc(sizeof(struct client), 1);*/

    struct client mass_client[10];

    memset(message_online.message_text.text, 0, 256);

    if ((msg_queue_key = ftok ("../queue.txt", PROJECT_ID)) == -1) {
        perror ("ftok");
        exit (1);
    }

    if ((qid = msgget (msg_queue_key, IPC_CREAT | QUEUE_PERMISSIONS)) == -1) {
        perror ("msgget");
        exit (1);
    }

    printf ("Server: Hello, World!\n");

    while (1) {
        // read an incoming message
        int flag_client = 0;

        if (msgrcv (qid, &message, sizeof (struct message), 0, 0) == -1) {
            perror ("msgrcv");
            exit (1);
        }

        printf("Type = %ld\n", message.message_type);

        if(message.message_type == 2){
            mass_client[count_client].client_queue_id = message.message_text.queue_id;
            strncpy(mass_client[count_client].client_name, message.message_text.text,20);

            printf("User %s online!\n", mass_client[count_client].client_name);

            strncat(message_online.message_text.text, mass_client[count_client].client_name, 20);
            //strncat(message_online.message_text.text, "\n", 1);
            
            message_online.message_type = 3;

            count_client++;
        
            for(int i = 0; i < count_client; i++){
                if (msgsnd (mass_client[i].client_queue_id, &message_online, sizeof (struct message_text), 0) == -1) {  
                    perror ("msgget");
                    exit (1);
                }
            }
        }

        printf ("Server: message received.\n");
        printf("Message from %d\n", message.message_text.queue_id);
        printf("%s\n",message.message_text.text);
        
        int client_qid = message.message_text.queue_id;
        message.message_text.queue_id = qid;

        // send reply message to client

        for(int i = 0; i < count_client && message.message_type != 2; i++){
            if (msgsnd (mass_client[i].client_queue_id, &message, sizeof (struct message_text), 0) == -1) {  
                perror ("msgget");
                exit (1);
            }
            
            printf ("Server: response sent to client - %d.\n", mass_client[i].client_queue_id);
        }
        
        
    }
}