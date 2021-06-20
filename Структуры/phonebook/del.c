#include "phbook.h"
#include "print_book.h"

extern unsigned char last_add;

char last_del = -1; //позиция последнего удаленного (если == -1, то после последнего доавления никого не удаляли)

void del_abonent(){//удаление абонента
    unsigned int number_abonent = 0;
    
    print_dir();

    printf("\n\tRemoving a subscriber\n");
    printf("Enter the subscriber number(1 - %d): ",N);
    scanf("%u",&number_abonent);

    number_abonent--;
    
    if(number_abonent < last_add){//существует ли выбранный для удаления абонент
        memset(abonents[number_abonent].name,0,32);
        memset(abonents[number_abonent].surname,0,32);
        memset(abonents[number_abonent].phone,0,12);
        last_del = number_abonent;
        last_add = (last_del == (last_add - 1))? last_add - 1: last_add;
    }else{
        printf("Record with this number was not found!\n");
    }

}