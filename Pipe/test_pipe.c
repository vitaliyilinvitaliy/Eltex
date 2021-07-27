#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(void){
    int fd[2] = {0};
    //0 - read
    //1 - write

    char r_buf = 0;
    char hello[6] = "Hello";

    if(pipe(fd) == -1){
        perror("Pipe");
        exit(EXIT_FAILURE);
    }

    pid_t child = fork();

    if(-1 == child){
        perror("Fork");
        exit(EXIT_FAILURE);
    }
    
    if(child == 0){
        close(fd[1]);
        printf("Children:\n");
        while(read(fd[0], &r_buf, 1)){
            printf("%c",r_buf);
        }
        printf("\nRead end!\n");
        close(fd[0]);
        exit(EXIT_SUCCESS);
    }else{
        printf("Parent: Write\n");
        close(fd[0]);
        write(fd[1], hello, 6);
        close(fd[1]);
        exit(EXIT_SUCCESS);
    }
}