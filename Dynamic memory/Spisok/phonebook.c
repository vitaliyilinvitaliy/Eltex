#include <stdlib.h>
#include <stdio.h> 
#include <string.h>

#include "phonebook.h"

void clear_buffer(){
    char c;
    while ((c = getchar()) != EOF && c != '\n');
}

void add_abonent(){
    char name[32];
    char surname[32];
    char phone[16];

    struct phbook *record = malloc(sizeof(struct phbook));
    record->next = NULL;
    record->prev = NULL;

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
    strcpy(record->surname,surname);
    strcpy(record->name,name);
    strcpy(record->phone,phone);

    if(head == NULL){
        head = record;    
    }else{
        struct phbook *ptr = head;
        while(ptr->next != NULL) ptr = ptr->next;
        
        ptr->next = record;
        record -> prev = ptr;
        record -> next = NULL;
    }
}


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

    
    struct phbook *ptr = head;
    unsigned int index = 0;

    while(ptr != NULL){
        if(strcmp(name,ptr->name) == 0 && strcmp(surname,ptr->surname) == 0){
            printf("%d %s %s %s\n",index + 1,ptr->surname,ptr->name,ptr->phone);
        }
        ptr = ptr -> next;
        index++;
    }

    if(index == 0) printf("\n\t...Empty...\n");

    printf("\n...Press any key...");
}


void del_abonent(){
    
    struct phbook *ptr = head;
    struct phbook *del_el = NULL;
    
    unsigned int number_abonent = 0;
    unsigned int index = 1;

    char flag_del = 0;

    print_dir();

    printf("\n\tRemoving a subscriber\n");
    printf("Enter the subscriber number(1 - ...): ");
    scanf("%u",&number_abonent);

    while(ptr != NULL){
        if(index == number_abonent){
            del_el = ptr;
            if(head == del_el){

                if(head -> next != NULL){
                    head = head->next;
                    head -> prev = NULL;
                }else{
                    head = NULL;
                }
            }else{
                ptr = ptr->prev;
                if(del_el -> next == NULL){
                    ptr -> next = NULL;
                } 
                else{
                    ptr -> next = del_el -> next;
                } 
            }
            free(del_el);
            del_el = NULL;
            flag_del = 1;
            break;
        }

        ptr = ptr -> next;
        index++;
    }

    if(flag_del == 0){
        printf("Record with this number was not found!\n");
    }
}


void print_dir(){
    unsigned int index = 0;

    struct phbook *ptr = head;

    printf("\tPhonebook:\n");

    while(ptr != NULL){
        printf("%d %s %s %s\n",index + 1,ptr->surname,ptr->name,ptr->phone);
        ptr = ptr->next;
        index++;
    }

    if(index == 0) printf("\n\t...Empty...\n");

    printf("\n...Press any key...");
}
