#include "phbook.h"
#include "menu.h"

unsigned int size_phbk = 0;

void clear_buffer(){
    char c;

    while ((c = getchar()) != EOF && c != '\n');
}

int main(){
    
    menu();
}