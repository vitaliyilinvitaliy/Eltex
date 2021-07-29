#include "interface/interface.h"
#include "interface/registration/registration.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){

    if(Interface() == 1){
        exit(EXIT_FAILURE);
    }
    
    return EXIT_SUCCESS;
}