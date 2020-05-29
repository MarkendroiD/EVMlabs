#pragma once

#include "mySimpleComputer.h"
#include "myBigChars.h"

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

int index;
int value[5];
int accumulator;

struct itimerval nval, oval;

typedef struct{
	int in_out;
	int value;
}VARS;

void print_big(int a);
int *get_big(int a);
void print_term();

