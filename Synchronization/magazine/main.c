#include "fill_magazine.h"
#include "buyer.h"
#include "loader.h"

#include <pthread.h>
#include <stdlib.h>

int gMagazine[5] = {0};
int gFlagEnd = 0;


int main(void){
    srand(time(NULL));

    pthread_t tid_buyer[3];
    pthread_t tid_loader;

    pthread_create(&tid_loader, NULL, loader, NULL);

    for(int i = 0; i < 3; i++){
        pthread_create(&tid_buyer[i], NULL, buyer, &i);
    }

    pthread_join(tid_loader, NULL);

    for(int i = 0; i < 3; i++){
        pthread_join(tid_buyer[i], NULL);
    }

}