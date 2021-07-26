#include <stdio.h>

void clear_buffer(void){
    char c;

    while ((c = getchar()) != EOF && c != '\n');
}