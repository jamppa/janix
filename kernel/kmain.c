/*
   *
   *	kernel main - responsible for initializing kernel 
   *
   *	Jani Arvonen 2012
*/

#include "kernel.h"
#include <janix/tty.h>

static void init_kernel();
static void initialize_screen();
static void initialize_interrupts();
static void initialize_clock();
static void initialize_paging();

void kernel_main(){
	init_kernel();
	for (;;);
}

static void init_kernel(){
	initialize_screen();
	initialize_interrupts();
	initialize_clock();
	initialize_paging();
}

static void say_hello_to_devday() {
    u32_t* faulting_addr = (u32_t *)0xC0000000;
    u32_t hello_reaktor_devday = *faulting_addr;
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
    init_traps();
	putsk("Interrupts initialized!\n");
}

static void initialize_clock(){
	init_clock();
	putsk("Clock initialized!\n");
}

