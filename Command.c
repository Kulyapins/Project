#include "Memory.h"
#include <stdio.h>
#include <stdlib.h>

Command cmd[] = {
	{0170000, 0010000, "mov", do_mov, (ss1 | dd2)},
	{0170000, 0060000, "add", do_add, (ss1 | dd2)},
	{0170000, 0000000, "halt", do_halt, zero},
};

Arg get_mr(word w) {
	Arg res;
	int r = w & 7; //номер регистра
	int mode = (w >> 3) & 7; //номер моды
	switch (mode) {
		case 0:              //R0
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
	exit(0);
}

void do_add() {
	dd.val = ss.val + dd.val;
	w_write(dd.adr, ss.val);
}

void do_mov() {
	w_write(dd.adr, ss.val);
}

void do_nothing() {}

void b_write(Adress adr, byte b) {
	if (adr > 7) {  //в 64kb
		mem[adr] = b;
		
	} else { //в регистры
		if (b >> 7) {
			reg[adr] = (0xFF00 | b);
		}
		else {
			reg[adr] = (0xFF00 & b);
		}
	}
}

byte b_read(Adress adr) {
	return mem[adr];
}

word w_read(Adress a) {
	word w = ((word)mem[a + 1]) << 8;
	w = w | mem[a];
	return w;
}

void w_write(Adress adr, word w) {
	if (adr > 15) { //в 64kb
		byte b_w1 = ((byte) w);
		byte b_w2 = ((byte) (w >> 8));
		b_write(adr, b_w1);
		b_write(adr + 1, b_w2);
	}
	else { //в регистры
		reg[adr] = w;
	}
}
