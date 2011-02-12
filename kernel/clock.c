/*
   *	clock.c - clock/timer functions. Initialises PIT and handles clock interrupt 
   *
   *	Jani Arvonen 2011
 */


#include "kernel.h"

static u32_t pending_ticks = 0;

static void clock_int_handler(registers_t registers);

void init_clock(void){
	
	register_interrupt_handler(IRQ0, clock_int_handler);

	u32_t divisor = TIMER_DIV;

	out_byte(TIMER_CMD_PORT, TIMER_REPEAT_MODE);
	out_byte(TIMER_DATA_PORT, (u8_t)divisor & 0xff);		/* LSB */
	out_byte(TIMER_DATA_PORT, (u8_t)(divisor >> 8) & 0xff);			/* MSB */
}

void clock_int_handler(registers_t registers){

	pending_ticks++;
	if(pending_ticks == 100){
		pending_ticks = 0;
		putsk("clock interrupt!\n");
	}
}

