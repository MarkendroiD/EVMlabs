#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VARS 35

typedef struct{
	int index;
	char command[6];
	int operand;
	int consta;
	int var_flag;
	int goto_flag;
	int const_flag;
} SA_line;

typedef struct{
	int adress;
	//int value;
	char name[2];
} VARS;

SA_line arr[100] = {0};
VARS vars[MAX_VARS] = {0};
char str[100];
char sa_file[50];
char bas_file[50];
int k; // индекс ассемблера

char sti(char *str, int *num)//str to int
{
	*num = 0;
	int radix = 1;
	int n = strlen(str);
	int begin = 0;
	if(str[0] == '-') {
		begin = 1;
	}
	for(int i = n - 1; i >= begin; i--) {
		if(str[i] == '\n') {
			continue;
		}
		*num += (str[i] - 48) * radix;
		if(str[i] < 47 || str[i] > 58) {
			*num = 0;
			return 's';//не не числоо
		}
		radix *= 10;
	}
	if(begin == 1) {
		*num = -(*num);
	}
	return 'i';//число
}

int check_var(char *name)
{
	if(strlen(name) == 2 && name[1] != '\n')
		return -1;
		
	if(strlen(name) > 2 || name[0] < 64 || name[0] > 90)
		return -1;
	return 0;
}

int find_var(char *name)
{
	name[1] = '\0';
	for(int index = 0; index < MAX_VARS; index++) {
		if(strcmp(vars[index].name, name) == 0)
			return index;
	}
	return -1;
}

int make_var(char *name)
{
	int index = 0;
	while(vars[index].name[0] != '\0')
		index++;
	name[1] = '\0';
	strcpy(&vars[index].name[0], name);
	vars[index].adress = 0;
	return index;
}

int arith(char *tok, char *right)
{
	int tmp = 0;
	if (strcmp(tok, "+") == 0) {
		strcpy(arr[k].command, "ADD");
	}else if (strcmp(tok, "-") == 0) {
		strcpy(arr[k].command, "SUB");
	}else if (strcmp(tok, "/") == 0) {
		strcpy(arr[k].command, "DIVIDE");
	}else if (strcmp(tok, "*") == 0) {
		strcpy(arr[k].command, "MUL");
	}else
		return -1;
	
	//tok = strtok(NULL, " ");
	if(right != NULL && strcmp(right, "\n") != 0) {
		if (check_var(right) == 0) {
			arr[k].operand = find_var(right);//присваеваем временно индекс, чтоб потом определить адресс переменной
			if(arr[k].operand == -1)
				arr[k].operand = make_var(right);
			arr[k].var_flag = 1;
			k++;
		}else if (sti(right, &tmp) == 'i') {
			arr[k].operand = find_var(right);//присваеваем временно индекс, чтоб потом определить адресс переменной
			if(arr[k].operand == -1)
				arr[k].operand = make_var(right);
			arr[k].const_flag = 1;
			arr[k].consta = tmp;//временное хранение коонстанты
			k++;
		}else {
			return -1;
		}
	}else {
		return -1;
	}
	return 0;
}

int make_input(char *tok)
{
	strcpy(arr[k].command, "READ");
	tok = strtok(NULL, " ");
	if(tok != NULL && check_var(tok) != -1) {
		arr[k].operand = find_var(tok);//присваеваем временно индекс, чтоб потом определить адресс переменной
		if(arr[k].operand == -1)
			arr[k].operand = make_var(tok);
		if((tok = strtok(NULL, " ")) != NULL && strcmp(tok, "\n") != 0){
			printf("overflow\t");
			return -1;
		}
		arr[k].var_flag = 1;
		k++;
	}else
		return -1;
	return 0;
}

int make_print(char *tok)
{
	strcpy(arr[k].command, "WRITE");
	tok = strtok(NULL, " ");
	if(tok != NULL && check_var(tok) != -1) {
		arr[k].operand = find_var(tok);//присваеваем временно индекс, чтоб потом определить адресс переменной
		if(arr[k].operand == -1)
			arr[k].operand = make_var(tok);
		if((tok = strtok(NULL, " ")) != NULL && strcmp(tok, "\n") != 0){
			printf("overflow\t");
			return -1;
		}
		arr[k].var_flag = 1;
		k++;
	}else
		return -1;
	return 0;
}

int make_goto(char *tok, char *com) 
{
	int temp = 0;
	strcpy(arr[k].command, com);
	tok = strtok(NULL, " ");
	if(tok != NULL && strcmp(tok, "\n") != 0) {
		if(sti(tok, &temp) != 's') {
			arr[k].operand = temp;
			arr[k].goto_flag = 1;
		}else {
			printf("nott int\t");
			return -1;
		}
		if((tok = strtok(NULL, " ")) != NULL && strcmp(tok, "\n") != 0){
			printf("overflow\t");
			return -1;
		}
		k++;
	}else
		return -1;
	return 0;
}

int make_let(char *tok)
{
	int temp = 0;
	tok = strtok(NULL, " ");
	if(tok != NULL && check_var(tok) != -1) {
		int temp_var = find_var(tok);//присваеваем временно индекс, чтоб потом определить адресс переменной
		if(temp_var == -1)
			temp_var = make_var(tok);
		tok = strtok(NULL, " ");
		if(tok != NULL && strcmp(tok, "=") == 0){
			tok = strtok(NULL, " ");
			if(tok != NULL && strcmp(tok, "\n") != 0) {
				if (check_var(tok) == 0) {
					strcpy(arr[k].command, "LOAD");
					arr[k].operand = find_var(tok);//присваеваем временно индекс, чтоб потом определить адресс переменной
					if(arr[k].operand == -1)
						arr[k].operand = make_var(tok);
					arr[k].var_flag = 1;
					k++;
				}else if (sti(tok, &temp) == 'i') {
					strcpy(arr[k].command, "LOAD");
					arr[k].operand = find_var(tok);//присваеваем временно индекс, чтоб потом определить адресс переменной
					if(arr[k].operand == -1)
						arr[k].operand = make_var(tok);
					arr[k].const_flag = 1;
					arr[k].consta = temp;//временное хранение коонстанты
					k++;
				}else {
					printf("wrong arguments\t");
					return -1;
				}
			}else {
				printf("wrong arguments\t");
				return -1;
			}
		}else {
			printf("wrong arguments\t");
			return -1;
		}
			
		tok = strtok(NULL, " ");
		if(tok != NULL && strcmp(tok, "\n") != 0) {
			char *right = strtok(NULL, " ");
			if(arith(tok, right) == 0) {
				strcpy(arr[k].command, "STORE");
				arr[k].operand = temp_var;//присваеваем временно индекс, чтоб потом определить адресс переменной
				arr[k].var_flag = 1;
				k++;
			}else {
				printf("wrong arith option\t");
				return -1;
			}	
		}else {
			strcpy(arr[k].command, "STORE");
			arr[k].operand = temp_var;//присваеваем временно индекс, чтоб потом определить адресс переменной
			arr[k].var_flag = 1;
			k++;
		}
			
	}else
		return -1;
	return 0;
}

int make_if(char *tok)
{
	int tmp = 0;
	char temp_var[5];
	char check;
	tok = strtok(NULL, " ");
	if(tok != NULL) {
		check = sti(tok, &tmp);
		if (check_var(tok) == 0 || check == 'i') {
			strcpy(temp_var, tok);
		}else {
			return -1;
		}
			
		tok = strtok(NULL, " ");
		if(tok != NULL) {
			if (strcmp(tok, "<") == 0) {
				strcpy(arr[k].command, "LOAD");
				if(check == 'i') {
					arr[k].operand = find_var(temp_var);//присваеваем временно индекс, чтоб потом определить адресс переменной
					if(arr[k].operand == -1)
						arr[k].operand = make_var(temp_var);
					arr[k].const_flag = 1;
					arr[k].consta = tmp;//временное хранение коонстанты
					k++;
				}else {
					arr[k].operand = find_var(temp_var);//присваеваем временно индекс, чтоб потом определить адресс переменной
					if(arr[k].operand == -1)
						arr[k].operand = make_var(temp_var);
					arr[k].var_flag = 1;
					k++;
				}
				char *right = strtok(NULL, " ");
				strcpy(tok, "-");
				if(arith(tok, right) == 0) {
					tok = strtok(NULL, " ");
					//if (strcmp(tok, "INPUT") == 0) {
						//return make_input(tok);
					//}else if (strcmp(tok, "PRINT") == 0) {
					//	return make_print(tok);
					//}else 
					if (strcmp(tok, "GOTO") == 0) {//jneg
						return make_goto(tok, "JNEG");	
					//}else if (strcmp(tok, "LET") == 0) {
					//	return make_let(tok);
					}else {
						return -1;
					}
				}else {
					printf("wrong arith option\t");
					return -1;
				}
			}else if (strcmp(tok, ">") == 0) {
				tok = strtok(NULL, " ");
				if(tok != NULL) {
					strcpy(arr[k].command, "LOAD");
					if(check == 'i') {
						arr[k].operand = find_var(tok);//присваеваем временно индекс, чтоб потом определить адресс переменной
						if(arr[k].operand == -1)
							arr[k].operand = make_var(tok);
						arr[k].const_flag = 1;
						arr[k].consta = tmp;//временное хранение коонстанты
						k++;
					}else {
						arr[k].operand = find_var(tok);//присваеваем временно индекс, чтоб потом определить адресс переменной
						if(arr[k].operand == -1)
							arr[k].operand = make_var(tok);
						arr[k].var_flag = 1;
						k++;
					}
					strcpy(tok, "-");
					if(arith(tok, temp_var) == 0) {
						tok = strtok(NULL, " ");
						//if (strcmp(tok, "INPUT") == 0) {
						//	return make_input(tok);
						//}else if (strcmp(tok, "PRINT") == 0) {
						//	return make_print(tok);
						//}else 
						if (strcmp(tok, "GOTO") == 0) {//jneg
							return make_goto(tok, "JNEG");	
						//}else if (strcmp(tok, "LET") == 0) {
							//return make_let(tok);
						}else {
							return -1;
						}
					}else {
						printf("wrong arith option\t");
						return -1;
					}
				}else {
					return -1;
				}
			}else if (strcmp(tok, "=") == 0) {
				strcpy(arr[k].command, "LOAD");
				if(check == 'i') {
					arr[k].operand = find_var(temp_var);//присваеваем временно индекс, чтоб потом определить адресс переменной
					if(arr[k].operand == -1)
						arr[k].operand = make_var(temp_var);
					arr[k].const_flag = 1;
					arr[k].consta = tmp;//временное хранение коонстанты
					k++;
				}else {
					arr[k].operand = find_var(temp_var);//присваеваем временно индекс, чтоб потом определить адресс переменной
					if(arr[k].operand == -1)
						arr[k].operand = make_var(temp_var);
					arr[k].var_flag = 1;
					k++;
				}
				char *right = strtok(NULL, " ");
				strcpy(tok, "-");
				if(arith(tok, right) == 0) {
					tok = strtok(NULL, " ");
					//if (strcmp(tok, "INPUT") == 0) {
					//	return make_input(tok);
					//}else if (strcmp(tok, "PRINT") == 0) {
						//return make_print(tok);
					//}else
					if (strcmp(tok, "GOTO") == 0) {//JZ
						return make_goto(tok, "JZ");	
					//}else if (strcmp(tok, "LET") == 0) {
						//return make_let(tok);
					}else {
						return -1;
					}
				}else {
					printf("wrong arith option\t");
					return -1;
				}
			}else {
				printf("wrong if option\t");
				return -1;
			}
			
		}else {
			return -1;
		}
	}else {
		return -1;
	}
}

int lex(int i)
{
	char *tok;
	int temp = 0;
	tok = strtok(str, " ");
	if(sti(tok, &temp) == 's' || temp != i) {
		printf("Wrong index\n");
		return -1;
	}
	arr[k].index = i;
	tok = strtok(NULL, " ");
	if(tok[strlen(tok) - 1] == '\n') {
		tok = strncpy(tok + 1, tok, strlen(tok) - 1);
	}
	if (strcmp(tok, "REM") == 0) {
		return 0;
	}else if (strcmp(tok, "INPUT") == 0) {
		return make_input(tok);
	}else if (strcmp(tok, "PRINT") == 0) {
		return make_print(tok);
	}else if (strcmp(tok, "GOTO") == 0) {//jump
		return make_goto(tok, "JUMP");	
	}else if (strcmp(tok, "END") == 0) {
		strcpy(arr[k].command, "HALT");
		arr[k].operand = 0;
		k++;
		tok = strtok(NULL, " ");
		if(strtok(NULL, " ") != NULL) {
			printf("overflow\t");
			return -1;
		}
	}else if (strcmp(tok, "LET") == 0) {
		return make_let(tok);
	}else if (strcmp(tok, "IF") == 0) {
		return make_if(tok);
	}else
		return 0;
	
	return 0;
}
int main(int argc, const char *argv[]) 
{
	
	if(argc != 3) {
		printf("Wrong number of arguments(basic)\n");
		return 0;
	}
	strcpy(bas_file, argv[1]);
	strcpy(sa_file, argv[2]);
	printf("\nTranslation %s from basic to assembler...\n", bas_file);
	FILE *f;
	f = fopen(bas_file, "r");
	int i = 10;
	k = 0;
	int check = 0;
	if(f != NULL) {
		for (int j = 0; j < MAX_VARS; j++) 
			vars[j].name[0] = '\0';
		while(fgets(str, 100, f) != NULL) {
			check = lex(i);
			if(check == -1) {
				printf("Syntax error: %d str\n", i);
				break;
			}
			i += 10;
		}
	} else
		printf("Could't open file %s!\n", bas_file);
	fclose(f);
	
	if (check == 0) {
		int end = k;
		for (int j = 0; j < end; j++) {
			if(arr[j].var_flag == 1) {
				if (vars[arr[j].operand].adress == 0) {
					vars[arr[j].operand].adress = k;
					arr[j].operand = k;
					strcpy(arr[k].command, "=");
					k++;
				}else 
					arr[j].operand = vars[arr[j].operand].adress;
				arr[j].var_flag = 0;
			}else if(arr[j].goto_flag == 1) {
				int g;
				for (g = 0; g < end; g++) {
					if(arr[j].operand == arr[g].index)
						break;
				}
				if(g == end) {
					printf("Error: GOTO adress out of programm!!!\n\n");
					return -1;
				}else {
					arr[j].operand = g;
					arr[j].goto_flag = 0;
				}//else 
			}else if(arr[j].const_flag == 1) {
				if (vars[arr[j].operand].adress == 0) {
					vars[arr[j].operand].adress = k;
					arr[j].operand = k;
					arr[k].operand = arr[j].consta;
					strcpy(arr[k].command, "=");
					k++;
				}else 
					arr[j].operand = vars[arr[j].operand].adress;
				arr[j].const_flag = 0;
			}
		}
		/*for (int j = 0; j < k; j++) {
			if(strcmp(arr[j].command, "=") == 0) 
				printf("%.2d %-3s %+.4d\n", j, arr[j].command, arr[j].operand);
			else
				printf("%.2d %-6s %.2d\n", j, arr[j].command, arr[j].operand);
		}*/

		//printf("\n\n\n");
		
		f = fopen(sa_file, "w");
		
		if (f != NULL) {
			for (int j = 0; j < k; j++) {
				if(strcmp(arr[j].command, "=") == 0) 
					fprintf(f, "%.2d %-3s %+.4d\n", j, arr[j].command, arr[j].operand);
				else
					fprintf(f, "%.2d %-6s %.2d\n", j, arr[j].command, arr[j].operand);
			}
			printf("\nTranslation from basic to assembler completed!!!\n\n");
			fclose(f);
			char cmd[100];
			strcpy(cmd, "./bin/sat ");
			strcat(cmd, sa_file);
			strcat(cmd, " ./res/prog.o");
			//printf("\n%s\n\n", cmd);
			system(cmd);
		}else
			printf("Could't open file %sTUTU!!\n", sa_file);
		
		
		
	}
	return 0;
}
