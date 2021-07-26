#include <curses.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>



void StartProcess(WINDOW *win, char *process_name){

    char process_full_name[256] = {0};


    pid_t proc_pid = fork();

    int stat = 0;

    if(proc_pid == 0){
        exit(execlp("vim","vim", process_name, NULL));
    }else{
        wait(&stat);
    }

     

}