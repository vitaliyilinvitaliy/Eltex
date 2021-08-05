#include "message.h"

#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

#include <mqueue.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/shm.h>
#include <sys/sem.h>

#include <stdlib.h>
#include <unistd.h>

#include <sys/mman.h>
#include <string.h>

int CreateQueueSystemV(struct parameters_system_v *params){
    key_t server_queue_key;
    int server_queue_id;
    int my_queue_id;

    int send_stat = 0;
    int ctl_stat = 0;

    my_queue_id = msgget(IPC_PRIVATE, MODE);

    if(my_queue_id == -1){
        perror("my q id");
        exit(EXIT_FAILURE);
    }

    server_queue_key = ftok(PATH_QUEUE, PROJECT_ID);

    if(server_queue_key == -1){
        perror("serv q key");
        exit(EXIT_FAILURE);
    } 

    server_queue_id = msgget(server_queue_key, 0);

    if(server_queue_id == -1){
        perror("serv q key");
        exit(EXIT_FAILURE);
    }

    (*params).server_queue_id = server_queue_id;
    (*params).server_queue_key = server_queue_key;
    (*params).my_queue_id = my_queue_id;

    return 0;
}

int CreateQueuePOSIX(char *user_name,struct parameters_POSIX *params){
    struct mq_attr my_attr;

    my_attr.mq_flags = 0;
    my_attr.mq_maxmsg = 10;
    my_attr.mq_msgsize = 256;
    my_attr.mq_curmsgs = 0;

    struct mq_attr server_attr;

    server_attr.mq_flags = 0;
    server_attr.mq_maxmsg = 10;
    server_attr.mq_msgsize = 256;
    server_attr.mq_curmsgs = 0;

    mqd_t my_queue_id = mq_open(user_name, O_CREAT|O_RDWR, MODE, &my_attr);

    if(my_queue_id == -1){
        perror("my open");
        exit(EXIT_FAILURE);
    }

    mqd_t server_queue_id = mq_open(SERVER_NAME, O_RDWR, &server_attr);

    if(server_queue_id == -1){
        perror("server open");
        exit(EXIT_FAILURE);
    }

    (*params).my_queue_id = my_queue_id;
    (*params).server_queue_id = server_queue_id;

    return 0;
}


int CreateShMemSystemV(struct parameters_shmem_system_v *params){
    int id_shmem = -1;
    int id_sem = -1;
    int id_serv_shmem = -1;
    int id_serv_sem = -1;

    struct shared_message_system_v *ptr_shmem = NULL;
    struct shared_message_system_v *ptr_serv_shmem = NULL;

    key_t key_shared_mem = shmget(IPC_PRIVATE, sizeof(struct parameters_shmem_system_v), IPC_CREAT|MODE);

    if(key_shared_mem == -1){
        perror("shmget private");
        exit(EXIT_FAILURE);
    }

    key_t key_serv_shared_mem = ftok(PATH_QUEUE, PROJECT_ID);

    if(key_serv_shared_mem == -1){
        perror("ftok serv");
        exit(EXIT_FAILURE);
    }

    id_shmem = shmget(key_shared_mem, sizeof(struct parameters_shmem_system_v), IPC_CREAT|MODE);

    if(id_shmem == -1){
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    id_serv_shmem = shmget(key_serv_shared_mem, sizeof(struct parameters_shmem_system_v), IPC_RMID|MODE);

    if(id_serv_shmem == -1){
        perror("shmget serv");
        exit(EXIT_FAILURE);
    }

    id_sem = semget(getpid(), 1, IPC_CREAT|MODE);

    if(id_sem == -1){
        perror("semget");
        exit(EXIT_FAILURE);
    }

    id_serv_sem = semget(SEMAPHORE_SERVER_KEY, 1, MODE);

    if(id_serv_sem == -1){
        perror("semget serv");
        exit(EXIT_FAILURE);
    }

    ptr_shmem = shmat(id_shmem, 0, 0);

    if(ptr_shmem == NULL){
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    ptr_serv_shmem = shmat(id_serv_shmem, 0, 0);

    if(ptr_serv_shmem == NULL){
        perror("shmat serv");
        exit(EXIT_FAILURE);
    }

    (*params).id_sem = id_sem;
    (*params).id_shmem = id_shmem;
    (*params).ptr_shmem = ptr_shmem;
    (*params).id_serv_sem = id_serv_sem;
    (*params).id_serv_shmem = id_serv_shmem;
    (*params).ptr_serv_shmem = ptr_serv_shmem;

}


int CreateShMemPOSIX(char *user_name, struct parameters_shmem_POSIX *params){
    int id_shmem = -1;
    sem_t *sem = NULL;
    int id_serv_shmem = -1;
    sem_t *serv_sem = NULL;
    struct shared_message_POSIX *ptr_shm = NULL;
    struct shared_message_POSIX *ptr_serv_shm = NULL;

    id_shmem = shm_open(user_name, O_CREAT|O_RDWR, MODE);

    if(id_shmem == -1){
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    if (ftruncate(id_shmem, sizeof(struct shared_message_POSIX)) != 0){
        perror("cannot set size");
        exit(EXIT_FAILURE);
    }

    id_serv_shmem = shm_open(SERVER_NAME, O_RDWR, MODE);

    if(id_serv_shmem == -1){
        perror("shm_open serv");
        exit(EXIT_FAILURE);
    }

    if (ftruncate(id_serv_shmem, sizeof(struct shared_message_POSIX)) != 0){
        perror("cannot set size serv");
        exit(EXIT_FAILURE);
    }

    sem = sem_open(user_name, O_CREAT|O_RDWR, MODE, 1);

    if(sem == MAP_FAILED){
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    serv_sem = sem_open(SERVER_NAME, O_RDWR, MODE, 1);

    if(serv_sem == MAP_FAILED){
        perror("sem_open server");
        exit(EXIT_FAILURE);
    }

    ptr_shm = (struct shared_message_POSIX*) mmap(0, sizeof(struct shared_message_POSIX), PROT_READ|PROT_WRITE, MAP_SHARED, id_shmem, 0);

    if(ptr_shm == MAP_FAILED){
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    if (mlock(ptr_shm, sizeof(struct shared_message_POSIX)) != 0){
        perror("cannot mlock");
        exit(EXIT_FAILURE);
    }

    ptr_serv_shm = (struct shared_message_POSIX*) mmap(0, sizeof(struct shared_message_POSIX), PROT_READ|PROT_WRITE, MAP_SHARED, id_serv_shmem, 0);

    if(ptr_shm == MAP_FAILED){
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    if (mlock(ptr_serv_shm, sizeof(struct shared_message_POSIX)) != 0){
        perror("cannot mlock serv");
        exit(EXIT_FAILURE);
    }

    (*params).id_shmem = id_shmem;
    (*params).id_serv_shmem = id_serv_shmem;
    (*params).sem = sem;
    (*params).serv_sem = serv_sem;
    (*params).ptr_shmem = ptr_shm;
    (*params).ptr_serv_shmem = ptr_serv_shm;

    return 0;
}