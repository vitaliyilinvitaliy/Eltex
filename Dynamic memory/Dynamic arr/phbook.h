#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define N 50

struct phbook
{
    char name[32];
    char surname[32];
    char phone[12];
}*abonents;

void clear_buffer();


