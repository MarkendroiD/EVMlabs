#include "mySimpleComputer.h"

int commands[NC] = { 0x10, 0x11, 0x20, 0x21, 0x30, 0x31, 0x32, 0x33, 0x40, 0x41, 0x42,
	0x43, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
	0x67, 0x68, 0x69, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76 };

int sc_memoryInit()
{
	for (int i = 0; i < N; i++){
		if (&arr[i] == NULL) return ERROR;
		arr[i] = 0;
	}
	return OK;
}

int sc_memorySet(int adress, int value)
{
	if (adress >= N || adress < 0) {
		sc_regSet(OM, 1);
		return ERROR;
	}
	else {
		arr[adress] = value;
		sc_regSet(OM, 0);
	}
		
	return OK;
}

int sc_memoryGet(int adress, int *value)
{
	if (adress >= N || adress < 0) {
		sc_regSet(OM, 1);
		return ERROR;
	}
	else {
		*value = arr[adress];
		sc_regSet(OM, 0);
	}
		
	return OK;
}


int sc_memorySave(char *filename)
{
	FILE *file = fopen(filename, "wb");
	
	if (!file) {
		printf("File not open!\n");
		return ERROR;
	}
	
	fwrite(arr, sizeof(int), N, file);
	fclose(file);
	return OK;
}

int sc_memoryLoad(char *filename)
{
	FILE *file = fopen(filename, "rb");
	
	if (!file) {
		printf("File not open!\n");
		return ERROR;
	}
	
	fread(arr, sizeof(int), N, file);
	fclose(file);
	return OK;
}

int sc_regInit(void)
{
	flag = 0;
	return OK;
}

int sc_regSet(int registr, int value)
{
	if (registr < 0 || registr > 4)
		return ERROR;
		
	if(value == 1) {
		value <<= registr;
		flag |= value;
	}else if (value == 0) {
		value = 1;
		value <<= registr;
		value = ~value;
		flag &= value;
	}else
		return ERROR;
		
	return OK;
}

int sc_regGet(int registr, int *value)
{
	if (registr < 0 || registr > 4) {
		sc_regSet(OV, 1);
		return ERROR;
	}
	
	*value = (flag >> registr) & 1;
	
	return OK;
}

int sc_commandEncode(int command, int operand, int *value)
{
	if (command >> 7 != 0 || operand >> 7 != 0) {
		sc_regSet(OV, 1);
		return ERROR;
	}
	int i;
	for (i = 0; i < NC; i++) {
		if (command == commands[i])	break;
	}
	
	if (i == NC) {
		sc_regSet(UC, 1);
		return ERROR;	
	}
	
	command <<= 7;
	command |= operand;
	*value = command;
	
	return OK;
}

int sc_commandDecode(int *command, int *operand, int value)
{
	if (value >> 14 != 0) {
		sc_regSet(OV, 1);
		return ERROR;
	}
		
	int temp_command, i;
	temp_command = (value >> 7) & 127;
	for (i = 0; i < NC; i++) {
		if (temp_command == commands[i])
			break;
	}
	if (i == NC) {
		sc_regSet(UC, 1);
		return ERROR;
	}else
		sc_regSet(UC, 0);
	*command = temp_command;
	*operand = value & 127;

	return OK;	
}
