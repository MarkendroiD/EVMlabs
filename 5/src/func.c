#include "func.h"

void do_command(enum keys k)
{
	int check = 0;
	char file_name[50];
	int sl = 0;
	
	switch (k) {
		case _l:
			printf("Enter filename to SAVE: ");
			fgets(file_name, 20, stdin);
			sl = strlen(file_name);
			file_name[sl - 1] = '\0';
			check = sc_memorySave(file_name);
			if(check != -1)
				printf("OK!\n\n");
			break;
		case _s:
			printf("Enter file name to LOAD: ");
			fgets(file_name, 20, stdin);
			sl = strlen(file_name);
			file_name[sl - 1] = '\0';
			check = sc_memoryLoad(file_name);
			if(check != -1)
				printf("OK!\n\n");
			break;
		case _r:
				sc_regSet(IG, 0);

				rk_mytermrergtime(0, 0, 0, 0, 0);

				signal(SIGALRM, inst_counter);

				nval.it_interval.tv_sec = 1;
				nval.it_interval.tv_usec = 0;
				nval.it_value.tv_sec = 1;
				nval.it_value.tv_usec = 0;

				setitimer(ITIMER_REAL, &nval, &oval);

				while(1) {
					sc_regGet(IG, &value[3]);
					if (index >= N - 1 || value[3] == 1) {
						alarm(0);
						break;
					}
					//Каждый сигнал, генерируемый setitimer'ом уникален и требует предварительно повторного вызова signal
					signal(SIGALRM, inst_counter);
						
					enum keys _temp;
					rk_readkey(&_temp);
					if(_temp == _i) {
						alarm(0);
						signal(SIGUSR1, _reset);
						raise (SIGUSR1);
						break;
					}
					
					//pause();
				}
				
				//rk_mytermrergtime(0, 1, 0, 0, 1);
				
				tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios_default);
			
			break;
		case _t:
			inst_counter();
			break;
		case _i:
			alarm(0);
			signal(SIGUSR1, _reset);
			raise (SIGUSR1);
			break;
		case _q:
			printf("New value: \n");
			int tmp;
			scanf("%x", &tmp);
			arr[index] = tmp;
			break;
		case _c:
			buff_clear();
			break;
		case F5:
			printf("Enter new accumulator: ");
			int t_ac;
			scanf("%x", &t_ac);
			while(t_ac > 0xffff || t_ac < -0xffff) {
				printf("Inncorect value, try again\n");
				printf("Enter new accumulator: ");
				scanf("%x", &t_ac);
			}
			accumulator = t_ac;
			break;
		case F6:
			printf("Enter new index: ");
			int in_c;
			scanf("%d", &in_c);
			while(in_c >= N || in_c < 0) {
				printf("Out of mem, try again\n");
				printf("Enter new index: ");
				scanf("%d", &in_c);
			}
			index = in_c;
			break;
		case UP:
			if (index - 10 >= 0)
				index -= 10;
			else
				index += 90;
			break;
		case DOWN:
			if (index + 10 < 100)
				index += 10;
			else
				index -= 90;
			break;
		case LEFT:
			if (index % 10 != 0)
				index--;
			else
				index += 9;
			break;
		case RIGHT:
			if (index % 10 != 9)
				index++;
			else
				index -= 9;
			break;
		case ENTER://fix мб откатт
			printf("Enter new command and operand: \n");
			int temp = 0, temp1, temp2;
			scanf("%2x%2x", &temp1, &temp2);
			if (sc_commandEncode(temp1, temp2, &temp) == 1)
				sc_memorySet(index, temp);
			
			break;
	}
	return;
}

void inst_counter()
{
	CU();
    print_term();
}

void _reset(){
	sc_memoryInit();
	sc_regInit();
	index = 0;
	sc_regSet(IG, 1);
	buff_clear();
	accumulator = 0;
}

void buff_clear()
{
	buff_counter = 0;
	for(int h = 0; h < BUF_SIZE; h++) {
		buffer[h].in_out = 0;
		buffer[h].value = 0;
	}
}
