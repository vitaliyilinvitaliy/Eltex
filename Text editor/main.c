#include "window.h"

#define DEFAULT_NAME "newfile.txt"

int main(int argc, char *argv[]){
    if(argc == 1){
        window(DEFAULT_NAME);
    }else{
        window(argv[1]);
    }
}