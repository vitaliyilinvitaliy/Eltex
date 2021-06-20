#include "phbook.h"

extern unsigned char last_add;

void search_abonent(){
    char name[32];
    char surname[32];

    printf("\tSearch a subscriber\n");
    
    printf("Input surname: ");
    scanf("%32s",surname);
    clear_buffer();

    printf("Input name: ");
    scanf("%32s",name);
    clear_buffer();

    printf("\n");

    short int counter_ab = 0;

    for(int i = 0; i < N && i < last_add; i++){
        if(strcmp(name,abonents[i].name) == 0 && strcmp(surname,abonents[i].surname) == 0){
            printf("%d %s %s %s\n",i+1,abonents[i].surname,abonents[i].name,abonents[i].phone);
            counter_ab++;
        }
    }

    if(counter_ab == 0) printf("\n\t...Empty...\n");

    printf("\n...Press any key...");
}