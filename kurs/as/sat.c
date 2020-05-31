#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char str[100];
char sa_file[50];
char o_file[50];
int arr[100];

char sti(char *str, int *num)//str to int
{
	*num = 0;
	int radix = 1;
	int n = strlen(str);
	for(int i = n - 1; i >= 0; i--) {
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
	return 'i';//число
}
int lex(int i)
{
	char *tok;
	char check;
	int temp = 0;
	int com, op = 0;
	tok = strtok(str, " ");
	check = sti(tok, &temp);
	if(check == 's' || temp != i) {
		printf("Wrong index\n");
		return -1;
	}

	tok = strtok(NULL, " ");
	if (strcmp(tok, "READ") == 0)
		com = 0x10;
	else if (strcmp(tok, "WRITE") == 0)
		com = 0x11;
	else if (strcmp(tok, "LOAD") == 0)
		com = 0x20;
	else if (strcmp(tok, "STORE") == 0)
		com = 0x21;
	else if (strcmp(tok, "ADD") == 0)
		com = 0x30;
	else if (strcmp(tok, "SUB") == 0)
		com = 0x31;
	else if (strcmp(tok, "DIVIDE") == 0)
		com = 0x32;
	else if (strcmp(tok, "MUL") == 0)
		com = 0x33;
	else if (strcmp(tok, "JUMP") == 0)
		com = 0x40;
	else if (strcmp(tok, "JNEG") == 0)
		com = 0x41;
	else if (strcmp(tok, "JZ") == 0)
		com = 0x42;
	else if (strcmp(tok, "HALT") == 0)
		com = 0x43;
	else if (strcmp(tok, "ADDC") == 0)
		com = 0X65;
	else if (strcmp(tok, "=") == 0)
		com = 0;// для переменных
	else {
		printf("Wrong command\n");
		return -1;
	}

	tok = strtok(NULL, " ");
	
	if(tok[0] == '+') {
		check = sti(tok + 1, &op);
	}else if (tok[0] == '-') {
		check = sti(tok + 1, &op);
		op = - op;
	}else
		check = sti(tok, &op);
	
	if(check == 's') {
		printf("Wrong operand\n");
		return -1;
	}
	if(op > 127) {
		printf("Wrong operand, Max operand = 127\n");
		return -1;
	}
		
	arr[i] = (com << 7) | op;
	
	tok = strtok(NULL, " ");
	if (tok != NULL && tok[0] != ';') {
		printf("Wrong commentary\n");
		return -1;
	}
	
	return 0;
}
int main(int argc, const char *argv[]) 
{
	if(argc != 3) {
		printf("Wrong number of arguments(assembler)\n");
		return 0;
	}
	strcpy(sa_file, argv[1]);
	strcpy(o_file, argv[2]);
	printf("\nTranslation %s from assembler to machine commands...\n", sa_file);
	FILE *f;
	f = fopen(sa_file, "r");
	int i = 0;
	int check = 0;
	if(f != NULL) {
		for (int j = 0; j < 100; j++)
			arr[j] = 0;
		while(fgets(str, 100, f) != NULL) {
			check = lex(i);
			if(check == -1) {
				printf("Syntax error: %d str\n", i);
				break;
			}
			i++;
		}
	} else
		printf("Could't open file %s!!\n", sa_file);
	fclose(f);
	if (check != -1) {
		f = fopen(o_file, "wb");
		
		if (f != NULL) {
			fwrite(arr, sizeof(int), 100, f);
			 printf("\nTranslation from assembler to machine commands completed!!!\n\n");
		}else
			printf("Could't open file %s!!\n", o_file);
		
		fclose(f);
	}
	/*for (int i = 0; i < 15; i++)
        printf("%d ", arr[i]);*/

    printf("\n");
	return 0;
}
