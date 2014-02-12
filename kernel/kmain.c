#include "kernel.h"
#include "multiboot.h"
#include "mmap.h"
#include <janix/tty.h>

static void init_kernel();
static void initialize_screen();
static void initialize_interrupts();
static void initialize_clock();
static void initialize_paging();
static void initialize_gdt();

static void print_mmap(const mmap_t* mmap);

static mmap_t mmap;

void kernel_main(multiboot_info_t* mb) {
    mmap = get_mmap(mb);
	init_kernel(&mmap);
    sti();
    for(;;);
}

static void init_kernel(const mmap_t* mmap){
	initialize_screen(mmap);
    initialize_gdt();
	initialize_interrupts();
	initialize_paging();
    initialize_clock();
}

static void initialize_gdt() {
    init_gdt();
    printk("- GDT loaded\n");
}

static void initialize_paging() {
	init_paging();
	printk("- Paging enabled\n");
}

static void initialize_screen(const mmap_t* mmap){
	init_tty();
	clear();
	printk("Booting Janix 0.01\n******************\n");
    print_mmap(mmap);
}

static void initialize_interrupts(){
	init_intr();
    init_traps();
	printk("- Interrupts initialized\n");
}

static void initialize_clock(){
	init_clock();
	printk("- Clock enabled\n");
}

static void print_mmap(const mmap_t* mmap) {
    if(mmap->is_available){
        printk("\nAvailable physical RAM %d kb\n", mmap->mem_size);
    }    
}

