#include "func.h"
#include "myTerm.h"

void print_term()
{
	mt_clrscr();
	//bc_box(1, 1, 12, 63);//ячейки
	mt_gotoXY(1, 27);
	printf("Memory");
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
	mt_gotoXY(1, 69);
    printf("accumulator");
    mt_gotoXY(2, 70);
    //printf("%.4d", accumulator);
    
    bc_box(4, 64, 3, 24);//правая таб 2
    mt_gotoXY(4, 66);
    printf("instructionCounter");
    mt_gotoXY(5, 70);
    //printf("+%.4d", index);
    
    bc_box(7, 64, 3, 24);//правая таб 3
    mt_gotoXY(7, 69);
    printf("Operation");
    mt_gotoXY(8, 70);
    int command = 0;
	int operand = 0;
    //sc_commandDecode(&command, &operand, arr[index]);
    printf("+%.2x : %.2d", command, operand);
    
	bc_box(10, 64, 3, 24);//правая таб 4
	mt_gotoXY(10, 69);
    printf("Flags");
    mt_gotoXY(11, 68);
    sc_regGet(OV, &value[0]);
    sc_regGet(D0, &value[1]);
    sc_regGet(OM, &value[2]);
    sc_regGet(IG, &value[3]);
    sc_regGet(UC, &value[4]);
    
    
    if(value[0] == 0)
		printf("OV");
	else {
		mt_ssetbgcolor(red);
		printf("OV");
		mt_ssetbgcolor(def);
	}
	printf(" ");
	if(value[1] == 0)
		printf("D0");
	else {
		mt_ssetbgcolor(red);
		printf("D0");
		mt_ssetbgcolor(def);
	}
	printf(" ");
	if(value[2] == 0)
		printf("OM");
	else {
		mt_ssetbgcolor(red);
		printf("OM");
		mt_ssetbgcolor(def);
	}
	printf(" ");
	if(value[3] == 0)
		printf("IG");
	else {
		mt_ssetbgcolor(red);
		printf("IG");
		mt_ssetbgcolor(def);
	}
	printf(" ");
	if(value[4] == 0)
		printf("UC");
	else {
		mt_ssetbgcolor(red);
		printf("UC");
		mt_ssetbgcolor(def);
	}
	
    
	bc_box(13, 1, 10, 52);//big char
	// //print_big(arr[index]);
    
	bc_box(13, 53, 10, 35);//таблица keys
    mt_gotoXY(13, 55);
    printf("Keys:");
    mt_gotoXY(14, 54);
    printf("l  - load");
    mt_gotoXY(15, 54);
    printf("s  - save");
    mt_gotoXY(16, 54);
    printf("r  - run");
    mt_gotoXY(17, 54);
    printf("t  - step");
    mt_gotoXY(18, 54);
    printf("i  - reset");
    mt_gotoXY(19, 54);
    printf("F5 - accumulator");
    mt_gotoXY(20, 54);
    printf("F6 - instructionCounter");
    mt_gotoXY(21, 54);
    printf("ENTER - set command and operand");
    mt_gotoXY(14, 65);
    printf("q - new value");
    mt_gotoXY(15, 65);
    printf("c - clear Input/Output");
    
    mt_gotoXY(24, 1);
    printf("Input\\Output:\n\n");
    /*
    for(int h = 0; h < BUF_SIZE && buffer[h].in_out != 0; h++) {
		if (buffer[h].in_out == 1)
			printf(">> ");
		else
			printf("<< ");
		printf("%d\n", buffer[h].value);
	}
	*/
}
