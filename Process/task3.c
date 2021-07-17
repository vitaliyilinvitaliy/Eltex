#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>


int main(void){
    pid_t proc = -1;
    pid_t parent = getpid();

    int w = 0;

    proc = fork();

    if(getppid() == parent){
        execl("test","");
        exit(0);
    }

    waitpid(proc,&w,0);

}
