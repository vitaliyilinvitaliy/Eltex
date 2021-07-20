#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

extern int gMagazine[5];
extern int gFlagEnd;
extern pthread_cond_t c1;

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m2 = PTHREAD_MUTEX_INITIALIZER;

void *buyer(void *args){

    int myneed = 1000 + rand( )% 600;
    int i = 0;
    int num_buyer = *((int*)args);
    

    while(myneed > 0){
        for(int i = 0; i < 5; i++){
            pthread_mutex_lock(&m1);
            if(gMagazine[i] != 0){
                myneed -= gMagazine[i];
                printf("Buyer - %d: need = %d buy = %d\n", num_buyer, myneed, gMagazine[i]);
                gMagazine[i] = 0;
            }

            pthread_mutex_unlock(&m1);
            
        }

        sleep(1);
    }

    pthread_mutex_lock(&m2);
    gFlagEnd++;
    printf("Exit: Buyer - %d: need = %d flag = %d\n",num_buyer, myneed, gFlagEnd);
    pthread_mutex_unlock(&m2);

    
}