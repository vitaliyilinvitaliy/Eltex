#include "phbook.h"

extern unsigned char last_add;

void print_dir(){//вывод всего массива, до самого нижнего, добавленного абонента
    printf("\tPhonebook:\n");
    for(int i = 0; i < N && i < last_add; i++){
        printf("%d %s %s %s\n",i+1,abonents[i].surname,abonents[i].name,abonents[i].phone);
    }

    if(last_add == 0) printf("\n\t...Empty...\n");

    printf("\n...Press any key...");
}