#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

struct termios savetty;

int rk_mytermsave(void)
{
    struct termios tty;
    if (tcgetattr(STDIN_FILENO, &tty) == -1)
    {
        return 1;
    }
    else
    {
        savetty = tty;
        return 0;
    }
}

int rk_mytermrestore(void)
{
    if (tcsetattr(STDIN_FILENO, TCSANOW, &savetty) == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint)
{
    struct termios Settings;
    rk_mytermsave();
    Settings = savetty;

    if (regime == 1)
    {
        Settings.c_lflag &= (~ICANON);

        if (sigint == 1)
        {
            Settings.c_lflag &= (~ISIG);
        }
        else if (sigint == 0)
        {
            Settings.c_lflag |= ISIG;
        }

        if (echo == 1)
        {
            Settings.c_lflag &= (~ECHO);
        }
        else if (echo == 0)
        {
            Settings.c_lflag |= ECHO;
        }

        Settings.c_cc[VMIN] = vmin;
        Settings.c_cc[VTIME] = vtime;
    }
    else if (regime == 0)
    {
        Settings.c_lflag |= (ICANON | ECHO);
    }

    tcsetattr(0, TCSANOW, &Settings);
    return 0;
}