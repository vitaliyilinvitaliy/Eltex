#include "../terminal/term.h"
#include "../terminal/size_window.h"
#include "../terminal/sig_winch.h"

#include "./chat/window_chat.h"
#include "./input/window_input.h"
#include "./foundation/window_foundation.h"
#include "./color/init_color.h"
#include "./registration/registration.h"
#include "../message/receive_message.h"
#include "../message/message.h"

#include <ncurses.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/msg.h>
#include <pthread.h>
#include <string.h>

int Interface(void){

    char user_name[20];

    WINDOW *chat = NULL;
    WINDOW *input = NULL;
    WINDOW *online = NULL;

    int ch = -1;

    struct size_window *size_chat_input = NULL;
    size_chat_input = (struct size_window*) malloc(sizeof(struct size_window));

    struct my_parameters *my_param;
    my_param = (struct my_parameters*) malloc(sizeof(struct my_parameters));

    GetParamsMessage(my_param);

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

    pthread_t tid;

    int thread_receive = pthread_create(&tid, NULL, ReceiveMessage, my_param);
    pthread_detach(tid);

    Input(input, my_param);
    
    echo();
    curs_set(TRUE);
    endwin();

    TermStoreDefault();

    free(size_chat_input);

    int ctl_stat = msgctl((*my_param).my_queue_id, IPC_RMID, NULL);

    if(ctl_stat == -1){
        perror("ctl");
        exit(EXIT_FAILURE);
    }

    pid_t clear_pid = fork();
    if(clear_pid == 0){
        exit(execlp("clear", "clear", NULL));        
    }else{
        return EXIT_SUCCESS;
    }

}