#include <stdio.h>
#include <assert.h>

typedef unsigned char byte;
typedef unsigned short int word;
typedef word Adress;

#define MEMSIZE (64*1024)

byte mem[MEMSIZE];

void b_write(Adress adr, byte b);
byte b_read(Adress adr);
void w_write(Adress adr, word w);
word w_read(Adress adr);
void load_file ();

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

void b_write(Adress adr, byte b) {
	mem[adr] = b;
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
	mem[adr] = w;
	mem[adr + 1] = w >> 8;
}
