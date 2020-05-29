#include "func.h"

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
    mt_gotoXY(2, 73);
    printf("%.4d", accumulator);
    
    bc_box(4, 64, 3, 24);//правая таб 2
    mt_gotoXY(4, 69);
    printf("INSTR_COUNTER");
    mt_gotoXY(5, 73);
    printf("+%.4d", index);
    
    bc_box(7, 64, 3, 24);//правая таб 3
    mt_gotoXY(7, 71);
    printf("OPERATION");
    mt_gotoXY(8, 72);
    int command = 0;
	int operand = 0;
    sc_commandDecode(&command, &operand, arr[index]);
    printf("+%.2x : %.2d", command, operand);
    
	bc_box(10, 64, 3, 24);//правая таб 4
	mt_gotoXY(10, 73);
    printf("FLAGS");
    mt_gotoXY(11, 68);
    sc_regGet(OV, &value[0]);
    sc_regGet(D0, &value[1]);
    sc_regGet(OM, &value[2]);
    sc_regGet(IG, &value[3]);
    sc_regGet(UC, &value[4]);
    
    if(value[0] == 0)
		printf("OV");
	else {
		mt_ssetbgcolor(def);
		printf("OV");
		mt_ssetbgcolor(def);
	}
	printf(" ");
	if(value[1] == 0)
		printf("D0");
	else {
		mt_ssetbgcolor(def);
		printf("D0");
		mt_ssetbgcolor(def);
	}
	printf(" ");
	if(value[2] == 0)
		printf("OM");
	else {
		mt_ssetbgcolor(def);
		printf("OM");
		mt_ssetbgcolor(def);
	}
	printf(" ");
	if(value[3] == 0)
		printf("IG");
	else {
		mt_ssetbgcolor(def);
		printf("IG");
		mt_ssetbgcolor(def);
	}
	printf(" ");
	if(value[4] == 0)
		printf("UC");
	else {
		mt_ssetbgcolor(def);
		printf("UC");
		mt_ssetbgcolor(def);
	}
    
	bc_box(13, 1, 10, 52); 
    print_big(arr[index]); 
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

void print_big(int a)//вывод биг чар
{
	int bc[2];

	bc[0] = plus_top;
	bc[1] = plus_bot;
    mt_gotoXY(14, 2);
    bc_printbigchar(bc, 14, 3, red, green);
	int yy = 13;//координата вывода бигчара
	for(int i = 3; i >= 0; i--, yy+= 10) {
		int *b = NULL;
		int dig = (a >> (4 * i)) & 0xF;
		b = get_big(dig);
		bc_printbigchar(b, 14, yy, red, green);
    }
}

int *get_big(int a)//получение цифры бигчара
{
	int *arr = malloc(2 * sizeof(int));
	switch (a) {
		case 1:
			arr[0] = one_top;
			arr[1] = one_bot;
			break;
		case 2:
			arr[0] = two_top;
			arr[1] = two_bot;
			break;
		case 3:
			arr[0] = three_top;
			arr[1] = three_bot;
			break;
		case 4:
			arr[0] = four_top;
			arr[1] = four_bot;
			break;
		case 5:
			arr[0] = five_top;
			arr[1] = five_bot;
			break;
		case 6:
			arr[0] = six_top;
			arr[1] = six_bot;
			break;
		case 7:
			arr[0] = seven_top;
			arr[1] = seven_bot;
			break;
		case 8:
			arr[0] = eight_top;
			arr[1] = eight_bot;
			break;
		case 9:
			arr[0] = nine_top;
			arr[1] = nine_bot;
			break;
		case 0:
			arr[0] = zero_top;
			arr[1] = zero_bot;
			break;
		case 10:
			arr[0] = a_top;
			arr[1] = a_bot;
			break;
		case 11:
			arr[0] = b_top;
			arr[1] = b_bot;
			break;
		case 12:
			arr[0] = c_top;
			arr[1] = c_bot;
			break;
		case 13:
			arr[0] = d_top;
			arr[1] = d_bot;
			break;
		case 14:
			arr[0] = e_top;
			arr[1] = e_bot;
			break;
		case 15:
			arr[0] = f_top;
			arr[1] = f_bot;
			break;
		
	}
	
	return arr;
}
