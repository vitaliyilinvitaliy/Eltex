#include "message.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int SendMessageShMemPOSIX(char *message, struct my_parameters my_par){
    int sem_stat = -1;
    int pos_y_chat = 1;
    int pos_y_online = 1;
    
    bool flag_stop = false;

    unsigned int online_id = 0;

    struct parameters_shmem_POSIX *shmem_par = (struct parameters_shmem_POSIX *) my_par.parameters_queue;
    sem_t *sem = (*shmem_par).sem;
    int id_shm = (*shmem_par).id_shmem;
    struct shared_message_POSIX *ptr_shm = (*shmem_par).ptr_shmem;

    sem_t *serv_sem = (*shmem_par).serv_sem;
    int id_serv_shm = (*shmem_par).id_serv_shmem;
    struct shared_message_POSIX *ptr_shm_serv = (*shmem_par).ptr_serv_shmem;
    
    sem_wait(serv_sem);
   
    strncpy((*ptr_shm_serv).message_text, message, 256);
    (*ptr_shm_serv).type_message = TRUE_MESSAGE;
    
    sem_post(serv_sem);
}