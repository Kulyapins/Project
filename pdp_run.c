#include "Command.c"
#include <stdio.h>
#include <stdlib.h>
#include <error.h>

void load_file(const char * way) {
    FILE *data = fopen(way, "r");
    Adress adr;
    unsigned int x, k = 0, r = 0;
    word N;

    if (data == NULL) {
        perror(way);
        exit(errno);
    }
    
	while ((k = fscanf(data, "%hx%hx", &adr, &N) != EOF) && (k != 0)) {
		r = 1;
		if ((0 > adr) || (adr > MEMSIZE)){ 
			fprintf(stderr, "Error adress\n");
			exit(3);
		}
		for(int i = 0; i < N; i++) {
			if (fscanf(data, "%x", &x) == 0) {
				fprintf (stderr, "Zero bits\n");
				exit(3);
			}
			b_write(adr + i, x);
		}}
		if (!r) {
			fprintf (stderr, "Empty\n");
			exit(3);
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
	if(argv[1] == NULL){
		printf("Write addres to file in cmd");
		return 1;
	}
	load_file(argv[1]);
	run();
	return 0;
}


