/*
   *
   *	kernel main 
   *
   *	Jani Arvonen 2010
*/

#include "kernel.h"
#include <janix/tty.h>

static void init();
static void initialize_screen();
static void initialize_interrupts();

void kernel_main(){

	init();
	//asm volatile ("int $0x3");	// just test interrupts

	for (;;);
}

static void init(){
	initialize_screen();
	initialize_interrupts();
}

static void initialize_screen(){
	init_tty();	
	clear();
	putsk("Janix 0.0.1 (32-bit protected mode)\n");
}

static void initialize_interrupts(){
	init_intr();
	putsk("Interrupts initialised.\n");
}
