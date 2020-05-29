#include "func.h"

void _stop()
{
	//alarm(0);
	sc_regSet(IG, 1);
}

void CU()
{
	//sc_regInit();
	//sc_regSet(IG, 1);
	sc_regSet(OV, 0);
	sc_regSet(D0, 0);
	sc_regSet(OM, 0);
	sc_regSet(UC, 0);
	print_term();//но это не точно
	int tmp;
	int temp_var;
	if (sc_memoryGet(index, &temp_var) == -1)
		_stop();
	int op, com;
	if (sc_commandDecode(&com, &op, temp_var) == -1)
		_stop();
	else
		switch (com) {
			case 0x10: //READ   
				alarm(0);
				tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios_default);
				printf(">> ");
				scanf("%d", &tmp);
				buffer[buff_counter].value = tmp;
				buffer[buff_counter].in_out = 1;
				buff_counter++;
				if (tmp > 0xffff || tmp < -0xffff) {
					sc_regSet(OV, 1);
					_stop();
				}else if (sc_memorySet(op, tmp) == -1)
						_stop();
				else
					index++;
				if(value[3] == 0) {
					rk_mytermrergtime(0, 0, 0, 0, 0);
					setitimer(ITIMER_REAL, &nval, &oval);
				}
				break;
			case 0x11://WRITE
				if (sc_memoryGet(op, &tmp) == -1)
					_stop();
				else{
					buffer[buff_counter].value = tmp;
					buffer[buff_counter].in_out = -1;
					buff_counter++;
					index++;
				}
				break;
			case 0x20://LOAD
				if (sc_memoryGet(op, &tmp) == -1)
					_stop();
				else{
					accumulator = tmp;
					index++;
				}
				break;
			case 0x21://STORE
				if (sc_memorySet(op, accumulator) == -1)
					_stop();
				else
					index++;
				break;
			case 0x40://JUMP
				if(op >= N || op < 0) {
					sc_regSet(OM, 1);
					_stop();
				}else
					index = op;
				break;
			case 0x41://JNEG
				if(accumulator < 0) {
					if(op >= N || op < 0) {
						sc_regSet(OM, 1);
						_stop();
					}else
						index = op;
				}else
					index++;
				break;
			case 0x42://JZ
				if(accumulator == 0) {
					if(op >= N || op < 0) {
						sc_regSet(OM, 1);
						_stop();
					}else
						index = op;
				}else
					index++;
				break;
			case 0x43://HALT
				_stop();
				break;
			default://остальные операции для АЛУ
				if(ALU(com, op) == -1)
					_stop();
				else
					index++;
				break;
		}
}

int ALU (int command, int operand)
{
	int tmp;
	int tmp1;
	switch (command) {
		case 0x30: //ADD
			if(sc_memoryGet(operand, &tmp) == -1) {
				_stop();
				return -1;
			}else
				accumulator += tmp;
			break;
		case 0x31: //SUBB
			if(sc_memoryGet(operand, &tmp) == -1) {
				_stop();
				return -1;
			}else
				accumulator -= tmp;
			break;
		case 0x32: //DIVIDE
			if(sc_memoryGet(operand, &tmp) == -1) {
				_stop();
				return -1;
			}else  if (tmp == 0) {
				sc_regSet(D0, 1);
				_stop();
				return -1;
			}else 
				accumulator /= tmp;
			break;
		case 0x33: //MUL
			if(sc_memoryGet(operand, &tmp) == -1) {
				_stop();
				return -1;
			}else
				accumulator *= tmp;
			break;
		case 0x65: //ADDC
			
			if(sc_memoryGet(operand, &tmp) == -1 || sc_memoryGet(accumulator, &tmp1) == -1) {
				_stop();
				return -1;
			}else
				accumulator = tmp + tmp1;
			break;
	}
	return 0;
}


