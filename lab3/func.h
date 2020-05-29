#pragma once

#include "mySimpleComputer.h"

#define REC 'a'
#define BR "j"
#define BL "m"
#define TR "k"
#define TL "l"
#define VERT "x"
#define HOR "q"

#include <math.h>
#include <signal.h>
#include <sys/time.h>

#define BUF_SIZE 50

int index;
int value[5];
int accumulator;

struct itimerval nval, oval;

typedef struct{
	int in_out;//флаг ввода ввывода
	int value;
}VARS;

VARS buffer[BUF_SIZE];
int buff_counter;
int bc_printA (char *str);
int bc_box (int x1, int y1, int x2, int y2);

void print_term();

