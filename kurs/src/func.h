#pragma once

#include "mySimpleComputer.h"
#include "myBigChars.h"
#include "myReadkey.h"

#include <math.h>
#include <signal.h>
#include <sys/time.h>

#define BUF_SIZE 50

int index;
int value[5];
int accumulator;
struct termios termios_default;
struct itimerval nval, oval;

typedef struct{
	int in_out;//флаг ввода ввывода
	int value;
}VARS;

VARS buffer[BUF_SIZE];
int buff_counter;

void print_term();
void print_big(int a);
int *get_big(int a);
void do_command(enum keys k);
void inst_counter();
void _reset();
int ALU (int command, int operand);
void CU ();
void buff_clear();
