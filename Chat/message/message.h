#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include "../client.h"

#include <sys/ipc.h>
#include <ncurses.h>
#include <mqueue.h>

#define MODE 0666//0777//0660  00644

//Shared memory System V
#define SHARED_MEM_KEY 30002
#define SEMAPHORE_KEY 4000
#define SEMAPHORE_SERVER_KEY 4001

#define FALSE_MESSAGE 1
#define TRUE_MESSAGE 2
#define ONLINE_MESSAGE 3
#define STOP_SERVER 4

//System V
#define PATH_QUEUE "./queue.txt"
#define PROJECT_ID 'A'

//POSIX
#define SERVER_NAME "/server"

#define PRIORITY_ONLINE 1
#define PRIORITY_MESSAGE 2

//POSIX
struct parameters_POSIX{
    mqd_t server_queue_id;
    mqd_t my_queue_id;
};

//System V 
struct message_text{
    int queue_id;
    char text[256];
};
//System V 
struct message{
    long message_type;
    struct message_text message_text;
};

//System V 
struct parameters_system_v{
    key_t server_queue_key;
    int server_queue_id;
    int my_queue_id;
};

//Shared memory
struct shared_message{
    unsigned int type_message;
    char message_text[256];
    char online_list[256];
    int id_shar_mem;
    int id_sem_shm;
};

struct parameters_shmem_system_v{
    int id_shmem;
    int id_sem;
    int id_serv_shmem;
    int id_serv_sem;
    struct shared_message *ptr_shmem;
    struct shared_message *ptr_serv_shmem;  
};

/*struct parameters_shmem_POSIX{
    
};*/

//Общее
struct my_parameters{
    WINDOW *chat;
    WINDOW *online;
    char name[20];
    void *parameters_queue;
};

//System V 
int CreateQueueSystemV(struct parameters_system_v *);
int SendMessageSystemV(char *, struct my_parameters);
void *ReceiveMessageSystemV(void *);

//POSIX
int CreateQueuePOSIX(char *, struct parameters_POSIX *);
int SendMessagePOSIX(char *, struct my_parameters);
void *ReceiveMessagePOSIX(void *);

//Shared memory
int CreateShMemSystemV(struct parameters_shmem_system_v *);
int SendMessageShMemSystemV(char *, struct my_parameters);
void *ReceiveMessageShMemSystemV(void *);


#endif //_MESSAGE_H_