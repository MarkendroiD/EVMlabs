#include "myReadkey.h"

int rk_mytermrergtime(int regime, int vtime, int vmin, int echo, int sigint)
{
	struct termios options;
	
	if (tcgetattr(STDIN_FILENO, &options) != 0)
		return -1;
		
	if (regime == 1)
		options.c_lflag |= ICANON;
	else if (regime == 0)
		options.c_lflag &= ~ICANON;
	else
		return -1;
		
	if (regime == 0) {
		options.c_cc[VTIME] = vtime;
		options.c_cc[VMIN] = vmin;
		if (echo == 1)
			options.c_lflag |= ECHO;
		else if (echo == 0)
			options.c_lflag &= ~ECHO;
		else
			return -1;
			
		if (sigint == 1)
			options.c_lflag |= ISIG;
		else if (sigint == 0)
			options.c_lflag &= ~ISIG;
		else
			return -1;
	}
	
	if (tcsetattr(STDIN_FILENO, TCSANOW, &options) != 0)
		return -1;
	
	return 0;
}

int rk_readkey(enum keys *key)
{
	struct termios orig_options;
	char buf[16];
	int num_read;
	
	if (tcgetattr(STDIN_FILENO, &orig_options) != 0)
		return -1;
		
	if (rk_mytermrergtime(0, 0, 1, 0, 1) != 0)
		return -1;
		
	num_read = read(STDIN_FILENO, buf, 15);
	
	if (num_read < 0)
		return -1;
		
	buf[num_read] = '\0';
	
	if (strcmp(buf, "l") == 0)
		*key = _l;
	else if (strcmp(buf, "s") == 0)
		*key = _s;
	else if (strcmp(buf, "r") == 0)
		*key = _r;
	else if (strcmp(buf, "t") == 0)
		*key = _t;
	else if (strcmp(buf, "i") == 0)
		*key = _i;
	else if (strcmp(buf, "q") == 0)
		*key = _q;
	else if (strcmp(buf, "c") == 0)
		*key = _c;
	else if (strcmp(buf, "\n") == 0)
		*key = ENTER;
	else if (strcmp(buf, "\E[15~") == 0)
		*key = F5;
	else if (strcmp(buf, "\E[17~") == 0)
		*key = F6;
	else if (strcmp(buf, "\E[A") == 0)
		*key = UP;
	else if (strcmp(buf, "\E[B") == 0)
		*key = DOWN;
	else if (strcmp(buf, "\E[C") == 0)
		*key = RIGHT;
	else if (strcmp(buf, "\E[D") == 0)
		*key = LEFT;
	else
		*key = -2;
		
	if (tcsetattr(STDIN_FILENO, TCSANOW, &orig_options) != 0)
		return -1;

	return 0;
}

int rk_mytermrestore()
{
	struct termios options;
	FILE *f;

	if ((f = fopen("termsettings", "rb")) == NULL)
		return -1;
	if (fread(&options, sizeof(options), 1, f) > 0) {
		if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &options) != 0)
			return -1;
	}else
		return -1;

	return 0;
}

int rk_mytermsave()
{
	struct termios options;
	FILE *f;
	
	if (tcgetattr(STDIN_FILENO, &options) != 0)
		return -1;
	if ((f = fopen("termsettings", "wb")) == NULL)
		return -1;
	fwrite(&options, sizeof(options), 1, f);
	fclose(f);
	
	return 0;
}
