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
void load_file ();
void do_nothing();
void do_mov();
void do_add();
void do_halt();
void load_file();
void run();
Arg get_mr(word w);

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

void test_mem() {
	// пишем слово, читаем слово
	Adress t1 = 2;
	word w0 = 0x0b0a;
	w_write(t1, w0);
	word wres1 = w_read(t1);
	printf("%04hx = %04hx\n", w0, wres1);
	assert(w0 = wres1);
	
	// пишем 2 байта, читаем 1 слово 
	Adress t2 = 4;
	byte b1 = 0xcb;
	byte b0 = 0x0a;
	word w = 0xcb0a;
	b_write(t2, b0);
	b_write(t2+1, b1);
	word wres2 = w_read(t2);
	printf("ww/br \t %04hx = %02hhx%02hhx\n", wres2, b1, b0);
	assert(wres2 == w);
}

