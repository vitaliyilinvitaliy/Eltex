#include <stdio.h>
#include <stdlib.h>

#include "phbook.h"

extern unsigned int size_phbk;

void print_dir(){//вывод всего массива, до самого нижнего, добавленного абонента
    printf("\tPhonebook:\n");
    for(int i = 0; i < N && i < size_phbk; i++){
        printf("%d %s %s %s\n",i+1,abonents[i].surname,abonents[i].name,abonents[i].phone);
    }

    if(size_phbk == 0) printf("\n\t...Empty...\n");

    printf("\n...Press any key...");
}