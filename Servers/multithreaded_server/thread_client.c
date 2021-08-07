#include "thread_client.h"
#include "../time/time.h"

#include <string.h>
#include <unistd.h>

void *ThreadClient(void *args){
    char send_message[SIZE_SEND_MESSAGE] = {0};
    char name_client[SIZE_CLIENT_NAME] = {0};
    char str_time[SIZE_STR_TIME] = {0};

    struct sockaddr_in client;

    struct pthread_args *client_info = (struct pthread_args*)args;

    socklen_t size_sockaddr_in = (*client_info).size_cl;

    memset((void*)&client, 0, size_sockaddr_in);

    int server_socket = (*client_info).socket_server;
    strncpy(name_client, (*client_info).name_client, SIZE_CLIENT_NAME);
    memcpy((void*)&client, (void*)&(*client_info).client, size_sockaddr_in);
    
    sleep(10);//имитация деятельности

    strncat(send_message, "Hi, ", SIZE_SEND_MESSAGE);
    strncat(send_message, name_client, SIZE_SEND_MESSAGE);
    strncat(send_message, " current time: ", SIZE_SEND_MESSAGE);
    GetTime(str_time);
    strncat(send_message, str_time, SIZE_SEND_MESSAGE);
    
    sendto(server_socket, send_message, SIZE_SEND_MESSAGE, 0, (struct sockaddr*)&client, size_sockaddr_in);
}