#ifndef _COLOR_H_
#define _COLOR_H_

enum colors
{
	black = 30,
	red = 31,
	green = 32,
	yellow = 33,
	blue = 34,
	magenta = 35,
	cyan = 36,
	white = 37,
	reset = 0
};

int setfgcolor(enum colors COL);
int setbgcolor(enum colors COL);

#endif //_COLOR_H_

