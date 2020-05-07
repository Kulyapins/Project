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
		printf("%06o %06o", pc, w);
		pc = pc + 2;
		if (w == 0) {
			printf("halt ");
			do_halt();
		}
}

int main(int argc, char * argv[]) {
	load_file();
	run();
	return 0;
}

