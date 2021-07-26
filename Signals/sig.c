#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig){
    printf("Signal %i - %s\n", sig, sys_siglist[sig]);
    exit(EXIT_SUCCESS);
}

int test_finc_sleep(void){
    printf("test_finc_sleep\n");
    printf("My pid is %i\n", getpid());
    printf("Waiting...\n");

    sigset_t sset;
    struct sigaction sa;

    sigemptyset(&sset);
    sigprocmask(SIG_SETMASK, &sset, 0);
    sa.sa_handler = handler;
    sigaction(SIGTERM, &sa, 0);

    while(1) sleep(1);

    return EXIT_FAILURE;
}

int test_func_pause(void){
    printf("test_func_pause\n");
    printf("My pid is %i\n", getpid());
    printf("Waiting...\n");

    sigset_t sset;
    struct sigaction sa;

    sigemptyset(&sset);
    sigprocmask(SIG_SETMASK, &sset, 0);
    sa.sa_handler = handler;
    sigaction(SIGTERM, &sa, 0);

    while(1) pause();

    return EXIT_FAILURE;
}

int test_func_sigwait(void){
    printf("test_func_sigwait\n");
    printf("My pid is %i\n", getpid());
    printf("Waiting...\n");

    sigset_t sset;
    int sig;
    
    struct sigaction sa;

    sigemptyset(&sset);
    sigprocmask(SIG_SETMASK, &sset, 0);
    sa.sa_handler = handler;
    sigaction(SIGTERM, &sa, 0);
    
    while(!sigwait(&sset, &sig)){
       
    }

    return EXIT_FAILURE;
}

int main(int argc, char *argv[]){

    int number_func = 1;

    if(argc > 1){
        number_func = atoi(argv[1]);
    }

  
    switch (number_func)
    {
    case 1:
        return test_finc_sleep();

    case 2:
        return test_func_pause();

    case 3:
        return test_func_sigwait();
    
    default:
        printf("Function - %d: not not found!\n", number_func);
    }

    return EXIT_FAILURE;
}

//https://www.opennet.ru/docs/RUS/glibc/glibc-21.html