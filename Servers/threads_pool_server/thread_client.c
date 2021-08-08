#include "../time/time.h"
#include "queue.h"

#include <sys/msg.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>

unsigned int free_threads = SIZE_POOL;

pthread_mutex_t m_free = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m_queue = PTHREAD_MUTEX_INITIALIZER;


void *ThreadClient(void *args){
    int size_sockaddr_in = sizeof(struct sockaddr_in);
    char str_time[SIZE_STR_TIME] = {0};
    int *fd_queue = ((int*)args);

    struct message rcvmsg;
    struct message_text client_data;

    while(1){

        pthread_mutex_lock(&m_queue);
        msgrcv(*fd_queue,(void*)&rcvmsg, sizeof(struct message),  0, 0);
        pthread_mutex_unlock(&m_queue);

        printf("Thread: working\n");

        pthread_mutex_lock(&m_free);
        free_threads--;
        pthread_mutex_unlock(&m_free);

        memcpy((void*)&client_data,(void*)&rcvmsg.message_text,sizeof(struct message_text));
        printf("Thread: Client name - %s %d\n", client_data.name_client, client_data.socket_server);
        sleep(10);
        GetTime(str_time);
        sendto(client_data.socket_server, (void*)str_time, SIZE_STR_TIME, 0, (struct sockaddr*)&client_data.client, size_sockaddr_in);

        pthread_mutex_lock(&m_free);
        free_threads++;
        pthread_mutex_unlock(&m_free);

    }
}