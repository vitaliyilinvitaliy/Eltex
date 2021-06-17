#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define N 50

unsigned char last_add = 0;//позиция самого нижнего, добавленного абонента в массиве
char last_del = -1; //позиция последнего удаленного (если == -1, то после последнего доавления никого не удаляли)

struct directory
{
    char name[32];
    char surname[32];
    char phone[12];
}abonents[N];

void print_dir(){//вывод всего массива, до самого нижнего, добавленного абонента
    printf("\tPhonebook:\n");
    for(int i = 0; i < N && i < last_add; i++){
        printf("%d %s %s %s\n",i+1,abonents[i].surname,abonents[i].name,abonents[i].phone);
    }

    if(last_add == 0) printf("\n\t...Empty...\n");

    printf("\n...Press any key...");
}

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
        scanf("%s",abonents[number_add].surname);
        printf("Input name: ");
        scanf("%s",abonents[number_add].name);
        printf("Input number phone: ");
        scanf("%s",abonents[number_add].phone);

        last_del = -1;
    }else{
        printf("No memory, delete the entry!\n");
    }
}

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

void search_abonent(){
    char name[32];
    char surname[32];

    printf("\tSearch a subscriber\n");
    
    printf("Input surname: ");
    scanf("%s",surname);

    printf("Input name: ");
    scanf("%s",name);

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

void menu(){
    int menu_item = 0;

    while(1){
        menu_item = -1;

        printf ("\033[0d\033[2J");//\033[0d\033[2J - esc последовательность для очистки терминала
        printf ("\tMenu\n"
        "Input 1 to print the phone book\n"
        "Input 2 to add a subscriber\n"
        "Input 3 to delete the subscriber\n"
        "Input 4 to search for a subscriber\n"
        "Input 5 to exit the program\n\n"
        "Input: ");
        
        scanf("%d",&menu_item);
        printf ("\033[0d\033[2J");
        switch (menu_item)
        {
        case 1:
            print_dir();
            getchar();
            getchar();
            break;
        
        case 2:
            add_abonent();
            break;

        case 3:
            del_abonent();
            break;
        
        case 4:
            search_abonent();
            getchar();
            getchar();
            break;
        
        case 5:
            exit(0);
            break;
        
        default:
            break;
        }
        sleep(0);
    }
}


int main(){
    menu();
}