#include "../message/message.h"

#include <sys/types.h>
#include <sys/mman.h>

#include <semaphore.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

struct client_shm{
    sem_t *sem_client;
    int id_shmem;
    struct shared_message_POSIX *ptr_shm;
};

int main(void){
    int id_shmem = -1;
    sem_t *serv_sem = NULL;
    struct shared_message_POSIX *ptr_serv_shmem = NULL;

    struct client_shm client_mass[10];
    int counter_client = 0;

    bool flag_stop = false;

    id_shmem = shm_open(SERVER_NAME, O_CREAT|O_RDWR, MODE);

    if(id_shmem == -1){
        perror("shm_open serv");
        exit(EXIT_FAILURE);
    }

    serv_sem = sem_open(SERVER_NAME, O_CREAT|O_RDWR, MODE, 1);

    if(serv_sem == MAP_FAILED){
        perror("sem serv");
        exit(EXIT_FAILURE);
    }

    if (ftruncate(id_shmem, sizeof(struct shared_message_POSIX)) != 0){
        perror("cannot set size");
        return -1;
    }

    ptr_serv_shmem = mmap(0, sizeof(struct shared_message_POSIX), PROT_READ|PROT_WRITE, MAP_SHARED, id_shmem, 0);

    if(ptr_serv_shmem == MAP_FAILED){
        perror("mmap serv");
        exit(EXIT_FAILURE);
    }

    if (mlock(ptr_serv_shmem, sizeof(struct shared_message_POSIX)) != 0){
        perror("cannot mlock");
        return -1;
    }

    printf("start server\n");
    int val = -1;
    
    sem_getvalue(serv_sem,&val);
    printf("sem serv = %d\n", val);

    while(!flag_stop){
        sem_wait(serv_sem);
        switch ((*ptr_serv_shmem).type_message)
        {
        case FALSE_MESSAGE:

            break;
        case TRUE_MESSAGE:
            printf("Get message: %s\n",(*ptr_serv_shmem).message_text);
            for(int i = 0; i < counter_client; i++){
                //sem_wait(client_mass[i].sem_client);

                strncpy(client_mass[i].ptr_shm->message_text, (*ptr_serv_shmem).message_text, 256);
                client_mass[i].ptr_shm->type_message = TRUE_MESSAGE;
    
                //sem_post(client_mass[i].sem_client);
            }
            

            break;
        case ONLINE_MESSAGE:
            printf("Hi %s\n", (*ptr_serv_shmem).message_text);
            client_mass[counter_client].id_shmem = shm_open((*ptr_serv_shmem).message_text, O_RDWR, MODE);

            if(client_mass[counter_client].id_shmem == -1){
                perror("shm_open client");
                exit(EXIT_FAILURE);
            }

            client_mass[counter_client].sem_client = sem_open((*ptr_serv_shmem).message_text, O_RDWR, MODE, 1);

            if(client_mass[counter_client].sem_client == MAP_FAILED){
                perror("sem client");
                exit(EXIT_FAILURE);
            }

            if (ftruncate(client_mass[counter_client].id_shmem, sizeof(struct shared_message_POSIX)) != 0){
                perror("cannot set size client");
                return -1;
            }

            client_mass[counter_client].ptr_shm = mmap(0, sizeof(struct shared_message_POSIX), PROT_READ|PROT_WRITE, MAP_SHARED, client_mass[counter_client].id_shmem, 0);

            if(client_mass[counter_client].ptr_shm == MAP_FAILED){
                perror("mmap serv");
                exit(EXIT_FAILURE);
            }

            if (mlock(client_mass[counter_client].ptr_shm, sizeof(struct shared_message_POSIX)) != 0){
                perror("cannot mlock");
                return -1;
            }

            counter_client++;
            printf("Connect client\n");
            break;
        case STOP_SERVER:
            flag_stop = true;
            break;
        default:
            break;
        }
        (*ptr_serv_shmem).type_message = FALSE_MESSAGE;
        sem_post(serv_sem);
    }

    
    sem_close(serv_sem);
    sem_unlink(SERVER_NAME);
    shm_unlink(SERVER_NAME);
    munmap(ptr_serv_shmem, sizeof(struct shared_message_POSIX));
    
    return EXIT_SUCCESS;
}