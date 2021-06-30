#ifndef _PHBOOK_H_
#define _PHBOOK_H_

#define N 50

struct phbook
{
    char name[32];
    char surname[32];
    char phone[12];
}*abonents;

void clear_buffer();

#endif


