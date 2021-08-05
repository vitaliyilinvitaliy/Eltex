#include "message.h"

#include <sys/shm.h>
#include <sys/sem.h>

#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

void *ReceiveMessageShMemSystemV(void *args){
    int sem_stat = -1;
    int pos_y_chat = 1;
    int pos_y_online = 1;
    
    unsigned int online_id = 0;

    struct my_parameters *my_param = NULL;

    my_param = (struct my_parameters*) args;

    struct parameters_shmem_system_v *shmem_par = (struct parameters_shmem_system_v *) (*my_param).parameters_queue;
    int id_sem = (*shmem_par).id_sem;
    int id_shm = (*shmem_par).id_shmem;
    struct shared_message_system_v *ptr_shm = (*shmem_par).ptr_shmem;

    int id_serv_sem = (*shmem_par).id_serv_sem;
    int id_serv_shm = (*shmem_par).id_serv_shmem;
    struct shared_message_system_v *ptr_shm_serv = (*shmem_par).ptr_serv_shmem;
    

    if(ptr_shm_serv == NULL){
        perror("shmat serv");
        exit(EXIT_FAILURE);
    }

    while(semctl(id_serv_sem, 0, GETVAL, 0) && (*ptr_shm_serv).type_message != FALSE_MESSAGE);

    if(semctl(id_serv_sem, 0, SETVAL, 1) == -1){
        perror("semctl serv 1");
        exit(EXIT_FAILURE);
    }

    (*ptr_shm_serv).id_sem_shm = id_sem;
    (*ptr_shm_serv).id_shar_mem = id_shm;
    strncpy((*ptr_shm_serv).message_text, (*my_param).name, 20);

    (*ptr_shm_serv).type_message = ONLINE_MESSAGE;

    if(semctl(id_serv_sem, 0, SETVAL, 0) == -1){
        perror("semctl serv 0");
        exit(EXIT_FAILURE);
    }

    (*ptr_shm).type_message = FALSE_MESSAGE;
    
    if(ptr_shm == NULL) exit(EXIT_FAILURE);

    while(1){
        while(semctl(id_sem, 0, GETVAL, 0));

        if(semctl(id_sem, 0, SETVAL, 1) == -1){
            perror("semctl while 1");
            exit(EXIT_FAILURE);
        }
        
        switch ((*ptr_shm).type_message)
        {
        case TRUE_MESSAGE:
            for(int i = 0; i < strlen((*ptr_shm).message_text); i++){
                mvwaddch((*my_param).chat, pos_y_chat, i + 1, (*ptr_shm).message_text[i]);
            }
            pos_y_chat++;
            wrefresh((*my_param).chat);
            break;

        case ONLINE_MESSAGE:
            pos_y_online = 1;
            for(int i = 0; i < strlen((*ptr_shm).online_list); i++){
                if((*ptr_shm).online_list[i] == '\n'){
                    pos_y_online++;
                } 
                mvwaddch((*my_param).online, pos_y_online, i + 1, (*ptr_shm).online_list[i]);
            }
            
            wrefresh((*my_param).online);
            break;


        default:
            break;
        }

        (*ptr_shm).type_message = FALSE_MESSAGE;
        
        if(semctl(id_sem, 0, SETVAL, 0)){
            perror("semctl while 0");
            exit(EXIT_FAILURE);
        }
        
    }
}