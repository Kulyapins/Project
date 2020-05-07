#include "Memory.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	word mask;
	word opcode;
	char * name;
	void (*do_func)(void);
} Command;

typedef struct {
	word val; //значение аргумента
	word adr; //адрес аргумента
} Arg;
Arg ss, dd;

Arg get_mr(word w) {
	Arg res;
	int r = w & 3; //номер регистра
	int mode = (w >> 3) & 7; //номер моды
	switch (mode) {
		case 0:              //R3
			res.adr = r;
			res.val = reg[r];
			printf("R%o ", r);
			break;
		case 1:              //(R3)
			res.adr = reg[r];
			res.val = w_read(res.adr); //b_read
			printf("(R%o) ", r);
			break;
		case 2:              //(R3)+   #3
			res.adr = reg[r];
			res.val = w_read(res.adr);
			reg[r] = reg[r] + 2;
			if (r == 7) 
				printf("#%o ", res.val);
			else
				printf("(R%o)+ ", r);
			break;
		default:
			fprintf (stderr, "Mode %o NOT IMPLEMENTED YET!/n", mode);
			exit(1);
		}
	return res;
}

void do_halt() {
	printf("THE END\n");
	exit(0);
}

void do_add() {
	printf("add\n");
	
}

void do_mov() {
	printf("mov\n");
	w_write(dd.adr, ss.val);
}

void do_nothing() {}

Command cmd[] = {
	{0170000, 0010000, "mov", do_mov},
	{0170000, 0060000, "add", do_add},
	{0170000, 0000000, "halt", do_halt},
};
