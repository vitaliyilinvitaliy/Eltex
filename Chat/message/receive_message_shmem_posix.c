#include "message.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void *ReceiveMessageShMemPOSIX(void *args){
    int sem_stat = -1;
    int pos_y_chat = 1;
    int pos_y_online = 1;
    bool flag_stop = false;

    unsigned int online_id = 0;

    struct my_parameters *my_param = NULL;

    my_param = (struct my_parameters*) args;

    struct parameters_shmem_POSIX *shmem_par = (struct parameters_shmem_POSIX *) (*my_param).parameters_queue;
    sem_t *sem = (*shmem_par).sem;
    int id_shm = (*shmem_par).id_shmem;
    struct shared_message_POSIX *ptr_shm = (*shmem_par).ptr_shmem;

    sem_t *serv_sem = (*shmem_par).serv_sem;
    int id_serv_shm = (*shmem_par).id_serv_shmem;
    struct shared_message_POSIX *ptr_shm_serv = (*shmem_par).ptr_serv_shmem;
    
    sem_wait(serv_sem);
    
    strncpy((*ptr_shm_serv).message_text, (*my_param).name, 256);
    (*ptr_shm_serv).type_message = ONLINE_MESSAGE;

    sem_post(serv_sem);
 
    while(!flag_stop){
        sem_wait(sem);
        switch ((*ptr_shm).type_message)
        {
        case TRUE_MESSAGE:
            for(int i = 0; i < strlen((*ptr_shm).message_text); i++){
                mvwaddch((*my_param).chat, pos_y_chat, i + 1, (*ptr_shm).message_text[i]);
            }
            pos_y_chat++;
            wrefresh((*my_param).chat);
            break;
        
        default:
            break;
        }
        (*ptr_shm).type_message = FALSE_MESSAGE;
        sem_post(sem);
    }

}