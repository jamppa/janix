#include "kernel.h"
#include <janix/tty.h>

static void init_kernel();
static void initialize_screen();
static void initialize_interrupts();
static void initialize_clock();
static void initialize_paging();

void kernel_main(){
	init_kernel();
}

static void init_kernel(){
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
    init_traps();
	putsk("Interrupts initialized!\n");
}

static void initialize_clock(){
	init_clock();
	putsk("Clock initialized!\n");
}

