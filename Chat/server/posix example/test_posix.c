#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#define MSG_SIZE 128;

int send()
{
    struct mq_attr attr = {0, 10, 128, 0};
    mqd_t mq = mq_open("/test", O_RDWR | O_CREAT, 00644, &attr);
    char msg[128] = {0};
    strncpy(msg, "this_is_a_test", 128);
    mq_send(mq, msg, 128, 0);
}

int recv()
{
    struct mq_attr attr = {0, 10, 128, 0};
    mqd_t mq = mq_open("/test", O_RDWR | O_CREAT, 00644, &attr);
    char msg[128] = {0};
    int res = mq_receive(mq, msg, 128, NULL);
    if (res == -1)
    {
        printf("Errno: %d\n", errno);
    }
    else
    {
        printf("Message: %s\n", msg); 
    }
}

int main()
{
    //send();
    recv();
    return 0;
}