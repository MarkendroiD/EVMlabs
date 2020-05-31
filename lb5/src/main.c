#include "func.h"


int main()
{
	buff_clear();
	tcgetattr(STDIN_FILENO, &termios_default);
	sc_memoryInit();
	sc_regInit();
	index = 0;
	accumulator = 0;
	value[0] = 0;
	value[1] = 0;
	value[2] = 0;
	value[3] = 0;
	value[4] = 0;
	sc_regSet(IG, 1);
    enum keys choose;
    while(1) {
		print_term();
		rk_readkey(&choose);
		if(choose == -2)
			break;
		do_command(choose);
	}

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios_default);
    return 0;
}
