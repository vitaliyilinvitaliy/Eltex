#include "phbook.h"

extern unsigned int size_phbk;

void add_abonent(){//добавление абонента
    char name[32];
    char surname[32];
    char phone[16];

    printf("\tAdding a subscriber\n");    

    printf("Input surname: ");
    clear_buffer();
    scanf("%31s",surname);

    printf("Input name: ");
    clear_buffer();
    scanf("%31s",name);
    
    printf("Input number phone: ");
    clear_buffer();
    scanf("%15s",phone);
    
    if(abonents == NULL){
        abonents = malloc(sizeof(struct phbook));
    }else{
        abonents = realloc(abonents,(size_phbk + 1) * sizeof(struct phbook));
    }

    clear_buffer();
    strcpy(abonents[size_phbk].surname,surname);
    strcpy(abonents[size_phbk].name,name);
    strcpy(abonents[size_phbk].phone,phone);

    size_phbk++;
    
        //printf("No memory, delete the entry!\n");
}