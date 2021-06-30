#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

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
        abonents = (struct phbook*) malloc(sizeof(struct phbook));
    }else{
        abonents = (struct phbook*) realloc(abonents,(size_phbk + 1) * sizeof(struct phbook));
    }

    if(abonents == 0){
        perror("Add: Error malloc\realloc!\n");
        exit(EXIT_FAILURE);
    }

    clear_buffer();
    strcpy(abonents[size_phbk].surname,surname);
    strcpy(abonents[size_phbk].name,name);
    strcpy(abonents[size_phbk].phone,phone);

    size_phbk++;
}