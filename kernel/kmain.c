/*
   *
   *	kernel main 
   *
   *	Jani Arvonen 2010
*/

#include "kernel.h"

static void init();
static void initialize_screen();
static void initialize_interrupts();
static void initialize_keyboard();

void kernel_main(){

	init();
	asm volatile ("int $0x3");

	for (;;);
}

static void init(){
	initialize_screen();
	initialize_interrupts();
	initialize_keyboard();
}

static void initialize_screen(){
	init_screen();	
	clear();
	putsk("Janix 0.0.1 - Jani Arvonen 2010\n");
}

static void initialize_interrupts(){
	init_intr();
	putsk("Interrupts initialised.\n");
}

static void initialize_keyboard(){
	init_keyboard();
	putsk("Keyboard initialised.\n");
}
