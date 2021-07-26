#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


//argv[1] - PID
//argv[2] - number signal
int main(int argc, char *argv[]){
    if(argc != 3){
        printf("Error: Incorrect number of arguments!\n");
        exit(EXIT_FAILURE);
    }

    pid_t PID_signal = atoi(argv[1]);
    int number_signal = atoi(argv[2]);

    if(-1 == kill(PID_signal, number_signal)){
        printf("Error: Signal sending error");
        exit(EXIT_FAILURE);
    }else{
        printf("Signal %d - %d", number_signal, sys_siglist[number_signal]);
    }

    return EXIT_SUCCESS;
}