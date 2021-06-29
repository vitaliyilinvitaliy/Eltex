#ifndef _PHBOOK_H_
#define _PHBOOK_H_

struct phbook{
    char name[32];
    char surname[32];
    char phone[12];

    struct phbook *prev;
    struct phbook *next;
}*head;

void add_abonent();
void search_abonent();
void del_abonent();
void print_dir();

#endif //_PHBOOK_H_

