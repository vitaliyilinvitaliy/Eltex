#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "phonebook.h"



void menu(){
    char menu_item = 0;

    while(1){
        menu_item = -1;

        printf ("\033[0d\033[2J");//\033[0d\033[2J - esc последовательность для очистки терминала
        printf ("\tMenu\n"
        "Input 1 to print the phone book\n"
        "Input 2 to add a subscriber\n"
        "Input 3 to delete the subscriber\n"
        "Input 4 to search for a subscriber\n"
        "Input 5 to delete phone book\n"
        "Input 6 to exit the program\n\n"
        "Input: ");
        
        scanf("%c",&menu_item);
        printf ("\033[0d\033[2J");
        switch (menu_item - 48)
        {
        case 1://ASKII код 49 (49 - 48 = 1)
            print_dir();
            getchar();
            getchar();
            break;
        
        case 2://ASKII код 50 (50 - 48 = 2)
            add_abonent();
            break;

        case 3://ASKII код 51 (51 - 48 = 3)
            del_abonent();
            break;
        
        case 4://ASKII код 52 (52 - 48 = 4)
            search_abonent();
            getchar();
            break;

        case 5://ASKII код 53 (53 - 48 = 5)
            free_list();
            break;

        case 6://ASKII код 54 (54 - 48 = 6)
            free_list();
            exit(0);
            break;
        
        default:
            break;
        }
        sleep(0);
    }
}
