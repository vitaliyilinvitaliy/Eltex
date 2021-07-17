#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int a = 0;

void *func(void *args){
    int i = 0;
    int tmp = 0;

    for(i = 0; i < 1000; i++){
        tmp = a;
        tmp++;
        a = tmp;
    }
}

int main(void){
    
    pthread_t tid[1000];

    int ret = 0;

    for(int i = 1; i <= 1000; i++){
        ret = pthread_create(&tid[i - 1], NULL, func, NULL);
        if(ret != 0){
            perror("create");
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 1; i <= 1000; i++){
        ret = pthread_join(tid[i - 1], NULL);
        if(ret != 0){
            perror("join");
            exit(EXIT_FAILURE);
        }
    }

    printf("a = %d\n",a);

    return 0;
}
