#include "phbook.h"
#include "menu.h"


void clear_buffer(){
    char c;

    while ((c = getchar()) != EOF && c != '\n');
}

int main(){
    menu();
}