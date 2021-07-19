#include <curses.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void StartProcess(WINDOW *win, char *directory, char *process_name){

    char process_full_name[256] = {0};

    strcpy(process_full_name, directory);
    strcat(process_full_name, "/");
    strcat(process_full_name, process_name);


    //char *argv[] = {"/bin/bash", "bash", "-c", "/usr/bin/vim ./clear_subwindow.c", NULL};

    pid_t proc_pid = fork();

    int stat = 0;

    if(proc_pid == 0){
        //exit(execve(argv[0], argv + 1, NULL)); 
        exit(execl("text_editor", "./clear_subwindow.c",NULL)); //!!!!!!!!!!!!!!!!!!!!!
        //exit(execlp("/bin/bash", "bash" ,"-c", "/usr/bin/vim","./clear_subwindow.c", NULL));
        //exit(execlp("vim", "./clear_subwindow.c", NULL));
    }else{
        wait(&stat);
    }

     

}