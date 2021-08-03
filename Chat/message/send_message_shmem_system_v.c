#include "message.h"

#include <sys/shm.h>
#include <sys/sem.h>

#include <ncurses.h>
#include <string.h>

int SendMessageShMemSystemV(char *message, struct my_parameters params){
    int sem_stat = -1;

    char mess_send[256] = {0};
    strncpy(mess_send, params.name, 256);
    strncat(mess_send, ": ", 2);
    strncat(mess_send, message, 256);

    struct parameters_shmem_system_v *shmem_par = (struct parameters_shmem_system_v*) params.parameters_queue;

    int id_sem_serv = (*shmem_par).id_serv_sem;
    int id_shm_serv = (*shmem_par).id_serv_shmem;

    struct shared_message *ptr_shmem_serv = (struct shared_message *) (*shmem_par).ptr_serv_shmem;

    while (semctl(id_sem_serv, 0, GETVAL, 0) && (*ptr_shmem_serv).type_message != FALSE_MESSAGE);//wait

    semctl(id_sem_serv, 0, SETVAL, 1);

    memset((*ptr_shmem_serv).message_text, 0, 256);
    strncpy((*ptr_shmem_serv).message_text, mess_send, 256);
    (*ptr_shmem_serv).type_message = TRUE_MESSAGE;

    semctl(id_sem_serv, 0, SETVAL, 0);
}