/*
   *
   *	kernel main 
   *
   *	Jani Arvonen 2010
*/

#include "kernel.h"

void kernel_main(){

	init_screen();	
	clear();
	putsk("Janix 0.0.1 - Jani Arvonen 2010\n");

	init_intr();
	putsk("Initialized interrupts.\n");

	asm volatile ("int $0x3");

	for (;;);
}
