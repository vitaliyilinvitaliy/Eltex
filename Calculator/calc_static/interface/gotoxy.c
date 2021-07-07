#include <stdio.h>
#include <stdlib.h>

#include "getscreensize.h"


int gotoXY(int x, int y)
{
	int rows = 0, cols = 0;
	getscreensize(&rows, &cols);
	if (y <= rows && y >= 0 && x >= 0 && x <= cols)
	{
		printf("\033[%d;%dH", y, x);
		return 0;
	}
	else
	{
		return 1;
	}
}