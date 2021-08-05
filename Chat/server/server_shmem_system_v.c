#include "../message/message.h"

#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>

#include <sys/sem.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct client_shm
{
    int id_shm;
    int id_sem;
    struct shared_message_system_v *ptr_shm;
};


int main(){
    struct client_shm client_mass[10];

    char online_list[256] = {0};

    int counter_clinet = 0;

    int id_segment = -1;
    int id_sem_mass = -1;

    int stat_sem_del = -1;
    int stat_shmem_del = -1;

    bool flag_stop = false;

    struct shared_message_system_v *ptr_shared_mem = NULL;    

    printf("< Start server >\n");

    key_t server_key = ftok("../queue.txt", PROJECT_ID);

    if(server_key == -1){
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    id_segment = shmget(server_key, sizeof(struct shared_message_system_v), IPC_CREAT|MODE);

    if(id_segment == -1){
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    id_sem_mass = semget(SEMAPHORE_SERVER_KEY, 1, IPC_CREAT|MODE);

    if(id_sem_mass == -1){
        perror("semget");
        exit(EXIT_FAILURE);
    }

    ptr_shared_mem = shmat(id_segment, 0, 0);

    if(ptr_shared_mem == NULL){
        perror("shmat");
        exit(EXIT_FAILURE);
    }
    
    semctl(id_sem_mass, 0, SETVAL, 0);
    ptr_shared_mem->type_message = FALSE_MESSAGE;

    while(!flag_stop){
        while(semctl(id_sem_mass, 0, GETVAL, 0));//wait


        semctl(id_sem_mass, 0, SETVAL, 1);
        switch (ptr_shared_mem->type_message)
        {
        case FALSE_MESSAGE:
            break;
        
        case TRUE_MESSAGE:
            printf("Get message: %s\n", (*ptr_shared_mem).message_text);

            for(int i = 0; i < counter_clinet; i++){
                semctl(client_mass[i].id_sem, 0, SETVAL, 1);

                strncpy(client_mass[i].ptr_shm->message_text, (*ptr_shared_mem).message_text, 256);
                client_mass[i].ptr_shm->type_message = TRUE_MESSAGE;
                printf("send to %d Message: %s\n", client_mass[i].id_shm, client_mass[i].ptr_shm->message_text);

                semctl(client_mass[i].id_sem, 0, SETVAL, 0);
            }

            (*ptr_shared_mem).type_message = FALSE_MESSAGE;
            
            break;

        case ONLINE_MESSAGE:
            semctl(id_sem_mass, 0, SETVAL, 1);
            strncat(online_list, (*ptr_shared_mem).message_text, 256);
            strncat(online_list, "\n", 1);
            printf("Hi %s id = %d\n", (*ptr_shared_mem).message_text, (*ptr_shared_mem).id_shar_mem);

            client_mass[counter_clinet].id_sem = (*ptr_shared_mem).id_sem_shm;
            client_mass[counter_clinet].id_shm = (*ptr_shared_mem).id_shar_mem;
            
            client_mass[counter_clinet].ptr_shm = shmat((*ptr_shared_mem).id_shar_mem, 0, 0);

            if(client_mass[counter_clinet].ptr_shm == NULL){
                perror("shmat clinet");
            }

            (*ptr_shared_mem).type_message = FALSE_MESSAGE;
            
            counter_clinet++;

            for(int i = 0; i < counter_clinet; i++){
                strncpy(client_mass[i].ptr_shm->online_list, online_list, 256);
                client_mass[i].ptr_shm->type_message = ONLINE_MESSAGE;
            }

            semctl(id_sem_mass, 0, SETVAL, 0);
            break;

        case STOP_SERVER:
            flag_stop = true;
            break;

        default:
            break;
        }
        semctl(id_sem_mass, 0, SETVAL, 1);
    }

    stat_sem_del = semctl(id_sem_mass, 0, IPC_RMID, 0);

    if(stat_sem_del == -1){
        perror("semctl");
        exit(EXIT_FAILURE);
    }

    stat_shmem_del = shmdt(ptr_shared_mem);

    if(stat_shmem_del == -1){
        perror("shmdt");
        exit(EXIT_FAILURE);
    }
    

    return EXIT_SUCCESS;
}