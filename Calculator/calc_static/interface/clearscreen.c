#include <stdio.h>

int clrscr(void)
{
	printf("\E[H\E[2J\E[H");
	return 0;
}