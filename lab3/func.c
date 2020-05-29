#include "func.h"


void inst_counter()
{
    print_term();
}

int bc_box(int x1, int y1, int x2, int y2)
{
	int x, y;
	int i;
	int size_x = x1 + x2 - 1;
	int size_y = y1 + y2 - 1;
	
	mt_getscreensize(&x, &y);
	if ((x1 < 1) || (y1 < 1) || (x2 <= 0) || (y2 <= 0) || (size_x > x) 
	  || (size_y > y))
		return -1;
	mt_gotoXY(x1, y1);
	bc_printA(TL);
	for (i = y1 + 1; i < size_y; i++)
		bc_printA(HOR);
	bc_printA(TR);
	for (i = x1 + 1; i < size_x; i++) {
		mt_gotoXY(i, y1);
		bc_printA(VERT);
		mt_gotoXY(i, size_y);
		bc_printA(VERT);
	}
	mt_gotoXY(size_x, y1);
	bc_printA(BL);
	for (i = y1 + 1; i < size_y; i++)
		bc_printA(HOR);
	bc_printA(BR);
	return 0;
}
int bc_printA(char *str)
{
	printf("\E(0%s\E(B", str);
	return 0;
}