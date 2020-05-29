#pragma once

#include <stdio.h>
#include <stdlib.h>

#define OV 0 //OPERATION_OVERFLOW
#define D0 1 //DIVIDE_BY_0
#define OM 2 //OUT_OF_MEMORY
#define IG 3 //IGNORE_IMPULSE
#define UC 4 //UNKNOWN_COMMAND

enum{
	OK = 1,
	ERROR = -1,
	N = 100,
	NC = 38
};



int arr[N];

int flag;

int sc_memoryInit();

int sc_memorySet(int adress, int value);

int sc_memoryGet(int adress, int *value);

int sc_memorySave(char *filename);

int sc_memoryLoad(char * filename);

int sc_regInit(void);

int sc_regSet(int registr, int value);

int sc_regGet(int registr, int *value);

int sc_commandEncode(int command, int operand, int *value);

int sc_commandDecode(int *command, int *operand, int value);
