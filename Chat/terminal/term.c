#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdio.h>

struct termios default_conf; 
struct termios my_conf;


int TermSave(struct termios *savetty)
{
    struct termios tty;
    if (tcgetattr(fileno(stdout), &tty) == -1)
    {
        return 1;
    }
    else
    {
        (*savetty) = tty;
        return 0;
    }
}

int TermStore(struct termios *savetty)
{
    if (tcsetattr(fileno(stdout), TCSANOW, savetty) == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


//вызов только один раз в начале программы
int TermSaveDefault(void){
    return TermSave(&default_conf);
}

int TermStoreDefault(void){
    return TermStore(&default_conf);
}

//вызов только один раз, после настройки ncurses
int TermSaveMyConf(void){
    return TermSave(&my_conf);
}

int TermStoreMyConf(void){
    return TermStore(&my_conf);
}

