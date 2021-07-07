#include <stdio.h>
#include "color.h"

int setfgcolor(enum colors COL)
{
	if (COL == 0 || (COL <= 37 && COL >= 30))
	{
		printf("\033[0;%dm", COL);
		return 0;
	}
	else
	{
		return -1;
	}
}

int setbgcolor(enum colors COL)
{
	if (COL == 0 || (COL <= 37 && COL >= 30))
	{
		int c = (int)COL + 10;
		printf("\033[0;%dm", c);
		return 0;
	}
	else
	{
		return -1;
	}
}