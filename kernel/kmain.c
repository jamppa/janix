#include "kernel.h"
#include <janix/tty.h>

static void init_kernel();
static void initialize_screen();
static void initialize_interrupts();
static void initialize_clock();
static void initialize_paging();
static void initialize_gdt();

void kernel_main(/*struct multiboot *pmultiboot*/) {
	init_kernel();
}

static void init_kernel(){
	initialize_screen();
    initialize_clock();
    initialize_gdt();
	initialize_interrupts();
	initialize_paging();
}

static void initialize_gdt() {
    init_gdt();
    printk("- GDT loaded\n");
}

static void initialize_paging() {
	init_paging();
	printk("- Paging enabled\n");
}

static void initialize_screen(){
	init_tty();
	clear();
	printk("Booting Janix 0.01\n******************\n");
}

static void initialize_interrupts(){
	init_intr();
    init_traps();
    sti();
	printk("- Interrupts enabled\n");
}

static void initialize_clock(){
	init_clock();
	printk("- Clock enabled\n");
}

