#include "Command.h"
#include <stdio.h>
#include <stdlib.h>

void load_file() {
	FILE *data = NULL;
	Adress adr;
	unsigned int x;
	word N;
	data = fopen("D:/data.o", "r");
	
	if (data == NULL) {
		perror("data.o");
		exit(1);
	}

	while (fscanf(data, "%hx%hx", &adr, &N) == 2) {
		for (int i = 0; i < N; i++) {
			fscanf(data, "%x", &x);
			b_write(adr + i, x);
		}
	}
	fclose(data);
}

void run() {
	pc = 01000;
	while(1) {
		word w = w_read(pc);
		printf("%06o %06o ", pc, w);
		pc = pc + 2;
		for (int i = 0; i < sizeof(cmd)/sizeof(cmd[0]); i++) {
			if ((w & cmd[i].mask) == cmd[i].opcode) {
				printf("%s ", cmd[i].name);
				if (cmd[i].argum & ss1) {
					ss = get_mr(w >> 6);
				}
				if (cmd[i].argum & dd2) {
					dd = get_mr(w);
				}
				cmd[i].do_func();
				printf("\n");
			}
		}
	}
}

int main(int argc, char * argv[]) {
	load_file();
	run();
	return 0;
}
