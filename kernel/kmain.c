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
static void initialize_clock();
static void initialize_paging();

void kernel_main(){
	init();
	for (;;);
}

static void init(){
	initialize_screen();
	initialize_paging();
	initialize_interrupts();
	initialize_clock();
}

static void initialize_paging() {
	init_paging();
	putsk("Paging initialised.\n");
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

static void initialize_clock(){
	init_clock();
	putsk("Clock initialised.\n");
}
