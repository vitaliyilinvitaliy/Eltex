#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

extern int gMagazine[5];
extern int gFlagEnd;

pthread_mutex_t m3 = PTHREAD_MUTEX_INITIALIZER;

void *loader(void *args){
    int i = 0;

    while(gFlagEnd < 3){
        pthread_mutex_lock(&m3);

        i = rand() % 4;
        printf("Loader +200 in %d\n", i);
        gMagazine[i] += 200; 
        printf("Magazine:[%d][%d][%d][%d][%d]\n",gMagazine[0],gMagazine[1],gMagazine[2],gMagazine[3],gMagazine[4]);
        
        pthread_mutex_unlock(&m3);
        sleep(2);
    
    }

    printf("Loader: working day is over\n");
}