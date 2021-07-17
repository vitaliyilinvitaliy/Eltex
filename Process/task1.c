#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
    
    pid_t proc = fork();

    printf("pid = %d\n",proc);

    switch (proc)
    {
    case -1:
        perror("fork");
        exit(EXIT_FAILURE);
        break;
    case 0:
        printf("Child. getpid() = %d\n", getpid());
        printf("Child. getppid() = %d\n", getppid());
        break;
    default:
        
        printf("Parent getpid() = %d\n",getpid());
        printf("Parent. getppid() = %d\n", getppid());

        break;
    }
    exit(0);
}