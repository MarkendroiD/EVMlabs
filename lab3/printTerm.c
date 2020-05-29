#include "func.h"
#include "myTerm.h"

void print_term()
{
	mt_clrscr();
	bc_box(1, 1, 12, 63);//ячейки
	mt_gotoXY(1, 27);
	printf("MEMORY");
	mt_gotoXY(2, 2);
    
    for (int i = 0; i < 10; i++)
    {
		mt_gotoXY(i + 2, 2);
        for (int j = 0; j < 10; j++)
        {
			if(i * 10 + j == index) {
				mt_ssetbgcolor(cyan);
				if (arr[i * 10 + j] < 0)
					printf(" %.4d", arr[i * 10 + j]);
				else
					printf(" +%.4x", arr[i * 10 + j]);
				mt_ssetbgcolor(def);
			}else {
				if (arr[i * 10 + j] < 0)
					printf(" %.4d", arr[i * 10 + j]);
				else
					printf(" +%.4x", arr[i * 10 + j]);
			}
        }
    }
	
	bc_box(1, 64, 3, 24);//правая таб 1
	mt_gotoXY(1, 70);
    printf("ACCUMULATOR");
    mt_gotoXY(2, 70);
    printf("%.4d", accumulator);
    
    bc_box(4, 64, 3, 24);//правая таб 2
    mt_gotoXY(4, 69);
    printf("INSTR_COUNTER");
    mt_gotoXY(5, 70);
    printf("+%.4d", index);
    
    bc_box(7, 64, 3, 24);//правая таб 3
    mt_gotoXY(7, 71);
    printf("OPERATION");
    mt_gotoXY(8, 70);
    //int command = 0;
	//int operand = 0;
    //sc_commandDecode(&command, &operand, arr[index]);
    //printf("+%.2x : %.2d", command, operand);
    
	bc_box(10, 64, 3, 24);//правая таб 4
	mt_gotoXY(10, 73);
    printf("FLAGS");
    mt_gotoXY(11, 68);
    sc_regGet(OV, &value[0]);
    sc_regGet(D0, &value[1]);
    sc_regGet(OM, &value[2]);
    sc_regGet(IG, &value[3]);
    sc_regGet(UC, &value[4]);
    

	printf("OV");

	printf(" D0");

	printf(" OM");

	printf(" IG");

	printf(" UC");
    
	bc_box(13, 1, 10, 52);   
	bc_box(13, 53, 10, 35);
    mt_gotoXY(13, 55);
    printf("KEYS:");
    mt_gotoXY(14, 54);
    printf("l  - LOAD");
    mt_gotoXY(15, 54);
    printf("s  - SAVE");
    mt_gotoXY(16, 54);
    printf("r  - RUN");
    mt_gotoXY(17, 54);
    printf("t  - STEP");
    mt_gotoXY(18, 54);
    printf("i  - RESET");
    mt_gotoXY(19, 54);
    printf("F5 - ACCUMULATOR");
    mt_gotoXY(20, 54);
    printf("F6 - INSTR_COUNTER");
    mt_gotoXY(21, 54);
    printf("ENTER - SET com. and oper.");
    mt_gotoXY(14, 65);
    printf("q - NEW VALUE");
    mt_gotoXY(15, 65);
    printf("c - clear IN/OUT");
    
    mt_gotoXY(24, 1);
}
