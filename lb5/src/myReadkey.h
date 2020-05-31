#pragma once

#include <stdio.h>
//#include <sys/types.h>
//#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

enum keys{
	_l,
	_s,
	_r,
	_t,
	_i,
	_q,
	_c,
	F5,
	F6,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	ENTER,
};

int rk_readkey(enum keys *key);
int rk_mytermsave();
int rk_mytermstore();
int rk_mytermrergtime(int regime, int vtime, int vmin, int echo, int sigint);
