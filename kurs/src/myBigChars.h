#pragma once

#include "myTerm.h"

#define REC 'a'
#define BR "j"
#define BL "m"
#define TR "k"
#define TL "l"
#define VERT "x"
#define HOR "q"

enum BigChar {
	plus_top = 404232216,
	plus_bot = 404232447,
	one_top = 404232223,
	one_bot = 4279769112,
	two_top = 3233857791,
	two_bot = 4278387711,
	three_top = 4290822399,
	three_bot = 4290822336,
	four_top = 4291019715,
	four_bot = 3233857728,
	five_top = 4278387711,
	five_bot = 4290822336,
	six_top = 4278387711,
	six_bot = 4291019715,
	seven_top = 3233857791,
	seven_bot = 3233857728,
	eight_top = 4291019775,
	eight_bot = 4291019715,
	nine_top = 4291019775,
	nine_bot = 4290822336,
	zero_top = 3284386815,
	zero_bot = 4291019715,
	a_top = 4291019775,
	a_bot = 3284386755,
	b_top = 1069794111,
	b_bot = 1069794303,
	c_top = 50529279,
	c_bot = 4278387459,
	d_top = 3284386623,
	d_bot = 1069794243,
	e_top = 4278387711,
	e_bot = 4278387459,
	f_top = 4278387711,
	f_bot = 50529027
};

int bc_printA (char *str);
int bc_box (int x1, int y1, int x2, int y2);
int bc_printbigchar(int *a, int x, int y, enum colors c1, enum colors c2);
int bc_setbigcharpos (int *big, int x, int y, int value);
int bc_getbigcharpos (int *big, int x, int y, int *value);
int bc_bigcharwrite (int fd, int *big, int count);
int bc_charread (int fd, int *big, int need_count, int *count);
