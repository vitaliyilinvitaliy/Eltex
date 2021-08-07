#include "../config.h"

#include <time.h>
#include <string.h>

int GetTime(char *str_time){
    long int ttime;
    ttime = time(NULL);
    strncpy(str_time, ctime(&ttime), SIZE_STR_TIME);
    return 0;
}