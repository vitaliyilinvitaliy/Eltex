#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "phbook.h"
#include "print_book.h"

extern unsigned int size_phbk;

void del_abonent(){//удаление абонента
    unsigned int number_abonent = 0;
    
    print_dir();

    printf("\n\tRemoving a subscriber\n");
    printf("Enter the subscriber number(1 - %d): ",size_phbk);
    scanf("%u",&number_abonent);

    number_abonent--;
    
    if(number_abonent < size_phbk){
        strcpy(abonents[number_abonent].surname, abonents[size_phbk - 1].surname);
        strcpy(abonents[number_abonent].name, abonents[size_phbk - 1].name);
        strcpy(abonents[number_abonent].phone, abonents[size_phbk - 1].phone);

        size_phbk--;

        abonents = realloc(abonents,size_phbk * sizeof(struct phbook));

        if(abonents == 0){
            perror("Del: Error realloc!\n");
            exit(EXIT_FAILURE);
        }
    }else{
        printf("Record with this number was not found!\n");
    }

}

//lib/list.c