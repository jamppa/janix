/*
   *	keyboard.c - Simple keyboard driver
   *
   *	Jani Arvonen 2011
 */

#include "kernel.h"

static keyboard_t keyboard;

static void keyboard_int_handler(registers_t regs);
static int scan_keyboard();
static int is_keyboard_buffer_full(keyboard_t* kb);
static int is_ignorable_break(int scan_code);
static void debug_print(int scan_code);

void init_keyboard(){

	keyboard_t* kb = &keyboard; 
	kb->buffer_count = 0;	
	memset(kb->buffer, 0, KEYBOARD_BUFFER_SIZE);
	
	kb->buffer_head = kb->buffer_tail = kb->buffer;

	scan_keyboard();
	register_interrupt_handler(IRQ1, keyboard_int_handler);	
}

static void keyboard_int_handler(registers_t regs){

	keyboard_t* kb = &keyboard;
	int scan_code = scan_keyboard();

	if(is_ignorable_break(scan_code))
		return;

	if(kb->buffer_count < KEYBOARD_BUFFER_SIZE){
		*kb->buffer_head++ = scan_code;
		kb->buffer_count++;
		
		if(is_keyboard_buffer_full(kb))
			kb->buffer_head = kb->buffer;	

		// TODO: here somewhere we probably want to do tty_interrupt
		debug_print(scan_code);
	}
}

static int scan_keyboard(){

	int code = in_byte(KEYBOARD_IO);
	int temp = in_byte(PPI_PORT_B);
		
	out_byte(PPI_PORT_B, temp|0x80);	// disable
	out_byte(PPI_PORT_B, temp&0x7f);	// enable

	return code;
}

static int is_keyboard_buffer_full(keyboard_t* kb){
	if(kb->buffer_head == &kb->buffer[KEYBOARD_BUFFER_SIZE]){
		return 1;
	}
	return 0;
}

static int is_ignorable_break(int scan_code){
	if(scan_code & 0x80)
		return 1;
	//TODO: later, check here caps, shift, alt and ctrl breaks
	return 0;
}

static void debug_print(int scan_code){
	putsk("keyboard: got scan scode ");
	puthk(scan_code);	
	putsk("\n");
}

