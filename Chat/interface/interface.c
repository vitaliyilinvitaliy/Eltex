#include "../client.h"

#include "../terminal/term.h"
#include "../terminal/size_window.h"
#include "../terminal/sig_winch.h"

#include "./chat/window_chat.h"
#include "./input/window_input.h"
#include "./color/init_color.h"
#include "./registration/registration.h"
#include "../message/message.h"

#include <ncurses.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/mman.h>
#include <pthread.h>
#include <string.h>


int Interface(void){
    int ctl_stat = -1;
    char user_name[20];

    WINDOW *chat = NULL;
    WINDOW *input = NULL;
    WINDOW *online = NULL;

    int ch = -1;

    struct size_window *size_chat_input = NULL;
    size_chat_input = (struct size_window*) malloc(sizeof(struct size_window));

    struct my_parameters *my_param = NULL;
    my_param = (struct my_parameters*) malloc(sizeof(struct my_parameters));

    struct struct_type *my_queue = NULL;
    my_queue = (struct struct_type*) malloc(sizeof(struct struct_type));

    if(SizeWindow(size_chat_input) == 1){
        exit(EXIT_FAILURE);
    }

    TermSaveDefault();
    
    initscr();
    start_color();
    
    signal(SIGWINCH, SigWinch);
    box(stdscr, 0, 0);

    struct winsize sizews;
    ioctl(fileno(stdout), TIOCGWINSZ, (char*) &sizews);
    curs_set(FALSE);
    noecho();
    refresh();

    Registration(user_name);

    strncpy((*my_param).name, user_name, 20);

    refresh();

    chat = newwin(size_chat_input->chat_vertical, size_chat_input->chat_horizontal ,size_chat_input->chat_y, size_chat_input->chat_x);
    keypad(chat, TRUE);
    box(chat, 0 , 0);
    wmove(chat, 0, 1);
    wprintw(chat, " CHAT ");
    wrefresh(chat);

    (*my_param).chat = chat;

    InitInput(size_chat_input->input_x, size_chat_input->input_y, size_chat_input->input_horizontal, size_chat_input->input_vertical);
    input = newwin(size_chat_input->input_vertical, size_chat_input->input_horizontal ,size_chat_input->input_y, size_chat_input->input_x);
    keypad(input, TRUE);
    box(input, 0 , 0);
    wrefresh(input);

    online = newwin(size_chat_input->chat_vertical, sizews.ws_col - size_chat_input->chat_horizontal - 2,1, size_chat_input->chat_x + size_chat_input->chat_horizontal);
    keypad(online, TRUE);
    box(online, 0 , 0);
    wmove(online, 0, 1);
    wprintw(online, " ONLINE ");
    wrefresh(online);

    (*my_param).online = online;
    
    #if REALIZATION == POSIX
        CreateQueuePOSIX((*my_param).name, my_queue);
    #endif //POSIX

    #if REALIZATION == SYSTEM_V
        CreateQueueSystemV(my_queue);
    #endif //SYSTEM_V

    #if REALIZATION == SHARED_MEMORY_SYSTEM_V
        CreateShMemSystemV(my_queue);
    #endif //SHARED_MEMORY
    
    #if REALIZATION == SHARED_MEMORY_POSIX
        CreateShMemPOSIX((*my_param).name, my_queue);
    #endif //SHARED_MEMORY
    

    (*my_param).parameters_queue = my_queue;

    pthread_t tid; 

    int thread_receive = pthread_create(&tid, NULL, ReceiveMessage, my_param);
    pthread_detach(tid);

    Input(input, my_param);
    
    echo();
    curs_set(TRUE);
    endwin();

    TermStoreDefault();

    #if REALIZATION == POSIX
        //ctl_stat = ;
    #endif //POSIX

    #if REALIZATION == SYSTEM_V
        //ctl_stat = ;
    #endif //SYSTEM_V

    #if REALIZATION == SHARED_MEMORY_SYSTEM_V
        ctl_stat = semctl((*my_queue).id_sem, 0, IPC_RMID, NULL);

        if(ctl_stat == -1){
            perror("ctl");
            exit(EXIT_FAILURE);
        }

        ctl_stat = shmctl((*my_queue).id_shmem, IPC_RMID, NULL);

        if(ctl_stat == -1){
            perror("ctl");
            exit(EXIT_FAILURE);
        }

        shmdt((*my_queue).ptr_shmem);
        shmdt((*my_queue).ptr_serv_shmem);
    
    #endif //SHARED_MEMORY_SYSTEM_V
    
    #if REALIZATION == SHARED_MEMORY_POSIX
        sem_close((*my_queue).sem);
        sem_close((*my_queue).serv_sem);
        //sem_unlink((*my_param).name);
        //sem_unlink(SERVER_NAME);
        //shm_unlink((*my_param).name);
        //shm_unlink(SERVER_NAME);
        //munmap((*my_queue).ptr_shmem, sizeof(struct shared_message_POSIX));
        //munmap((*my_queue).ptr_serv_shmem, sizeof(struct shared_message));
    #endif //SHARED_MEMORY_POSIX

    free(size_chat_input);
    free(my_queue);
    free(my_param);

    

    //pid_t clear_pid = fork();
    //if(clear_pid == 0){
    //    exit(execlp("clear", "clear", NULL));        
    //}else{
        return EXIT_SUCCESS;
    //}

}