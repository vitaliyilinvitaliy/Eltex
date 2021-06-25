#include "phbook.h"

extern char last_del;

unsigned char last_add = 0;//позиция самого нижнего, добавленного абонента в массиве

void add_abonent(){//добавление абонента
    char name[32];
    char surname[32];
    char phone[16];

    unsigned char number_add = 0;

    printf("\tAdding a subscriber\n");    

    if(last_add < N){
        if(-1 == last_del){ 
            number_add = last_add;
            last_add++;
        }else{
            number_add = last_del;
        }

        printf("Input surname: ");
        clear_buffer();
        scanf("%31s",surname);

        printf("Input name: ");
        clear_buffer();
        scanf("%31s",name);
        
        printf("Input number phone: ");
        clear_buffer();
        scanf("%15s",phone);
        
        clear_buffer();
        strcpy(abonents[number_add].surname,surname);
        strcpy(abonents[number_add].name,name);
        strcpy(abonents[number_add].phone,phone);

        last_del = -1;
    }else{
        printf("No memory, delete the entry!\n");
    }
}