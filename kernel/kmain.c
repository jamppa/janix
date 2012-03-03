/*
   *
   *	kernel main 
   *
   *	Jani Arvonen 2012
*/

#include "kernel.h"
#include <janix/tty.h>

static void init();
static void initialize_screen();
static void initialize_interrupts();
static void initialize_clock();
static void initialize_paging();

static void do_page_fault();

void kernel_main(){
	init();
    //do_page_fault();
	for (;;);
}

static void init(){
	initialize_screen();
	initialize_interrupts();
	initialize_clock();
	initialize_paging();
}

static void initialize_paging() {
	init_paging();
	putsk("Paging initialized!\n");
}

static void initialize_screen(){
	init_tty();
	clear();
	putsk("Janix 0.0.1 (32-bit protected mode)\n");
}

static void initialize_interrupts(){
	init_intr();
	putsk("Interrupts initialized!\n");
}

static void initialize_clock(){
	init_clock();
	putsk("Clock initialized!\n");
}

static void do_page_fault() {

    int* fault_ptr = (int *)0xB0000000;
    *fault_ptr = 1;
}
