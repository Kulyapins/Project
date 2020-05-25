#include <stdio.h>
#include <assert.h>

typedef unsigned char byte;
typedef unsigned short int word;
typedef word Adress;

typedef struct {
	word mask;
	word opcode;
	char * name;
	void (*do_func)(void);
	int argum;
} Command;

typedef struct {
	word val; //значение аргумента
	word adr; //адрес аргумента
} Arg;
Arg ss, dd;

#define MEMSIZE (64*1024) //64kb memory
byte mem[MEMSIZE];
word reg[8]; //регистры 1..7

#define pc reg[7]
#define zero 0 //empty arg
#define ss1 1 //with ss
#define dd2 2 //with dd

void b_write(Adress adr, byte b);
byte b_read(Adress adr);
void w_write(Adress adr, word w);
word w_read(Adress adr);

void do_nothing();
void do_mov();
void do_add();
void do_halt();
void load_file();
void run();
Arg get_mr(word w);


