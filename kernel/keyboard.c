/*
   *	keyboard.c - Simple keyboard driver
   *
   *	Jani Arvonen 2011
 */

#include "kernel.h"
#include <janix/tty.h>

static keyboard_t keyboard;

static int shift = 0;
static int alt = 0;

static void keyboard_int_handler(registers_t regs);
static void keyboard_read(tty_t* tp);
static int scan_keyboard();
static int is_keyboard_buffer_full(keyboard_t* kb);
static int is_keyboard_buffer_read(keyboard_t* kb);
static int is_ignorable_break(int scan_code);
static unsigned char map_key(int scan_code);
static unsigned char map_shift_key(int scan_code);
static unsigned char map_alt_key(int scan_code);
static void read_char(tty_t* tp, unsigned char c);
static int set_special_key_state(int scan_code);
static int set_shift_key_state(int scan_code);
static int set_alt_key_state(int scan_code);

	// keymaps for original XT scancodes

static const unsigned char keymap[] = {
	0, 27,
	'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '+',
	8, 9,
	'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '}',
	0, 10, 0,
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', '|', '{',
	0, 0,
	'\'','z','x','c','v','b','n','m','<', 0, 0,
	0, '*', 0, 32,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	'-', 0, 0, 0, '+',
	0, 0, 0, 0, 0, 0, 0,
	'<',	
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static const unsigned char alt_keymap[] = {
	0, 0,
	0, '@', 0, '$', 0, 0, '{', '[', ']', '}', '\\', 0,
	0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	'~', 10, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0,
	'|',	
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static const unsigned char shift_keymap[] = {
	0, 27,
	'!', '\"', '#', ' ', '%', '^', '&', '*', '(', ')', '_', '=',	/* 13 */
	8, 9,
	'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', ']', '^',		/* 27 */
	10, 0,
	'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\"',			/* 40 */
	0, 0,
	'*', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ';', '>', '/',
	0, '*', 0, 32,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	'-', 0, 0, 0, '+',
	0, 0, 0, 0, 0, 0, 0,
	'>',	
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void init_keyboard(tty_t* tp){

	keyboard_t* kb = &keyboard; 
	kb->buffer_count = 0;	
	memset(kb->buffer, 0, KEYBOARD_BUFFER_SIZE);
	
	kb->buffer_head = kb->buffer_tail = kb->buffer;
	tp->dev_read = keyboard_read;

	scan_keyboard();
	register_interrupt_handler(IRQ1, keyboard_int_handler);	
}

static void keyboard_int_handler(registers_t regs){

	keyboard_t* kb = &keyboard;
	int scan_code = scan_keyboard();

	if(is_ignorable_break(scan_code))
		return;

	if(set_special_key_state(scan_code))
		return;

	if(kb->buffer_count < KEYBOARD_BUFFER_SIZE){
		*kb->buffer_head++ = scan_code;
		kb->buffer_count++;
		
		if(is_keyboard_buffer_full(kb))
			kb->buffer_head = kb->buffer;	

		tty_interrupt();
	}
}

static void keyboard_read(tty_t* tp){

	int scan_code;
	keyboard_t* kb = &keyboard;
	unsigned c;

	while(kb->buffer_count > 0){
		
		scan_code = *kb->buffer_tail++;
		if(is_keyboard_buffer_read(kb))
			kb->buffer_tail = kb->buffer;

		kb->buffer_count--;	
		c = map_key(scan_code & 0x7f);
		read_char(tp, c);	
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

static int is_keyboard_buffer_read(keyboard_t* kb){
	if(kb->buffer_tail == &kb->buffer[KEYBOARD_BUFFER_SIZE]){
		return 1;
	}
	return 0;
}

static int is_ignorable_break(int scan_code){
	if(scan_code & 0x80){
		if(scan_code != 0xaa && 
				scan_code != 0xb6)
			return 1;
	}
	return 0;
}

static unsigned char map_key(int scan_code){

	if(shift && alt)
		return 0;

	if(shift)
		return map_shift_key(scan_code) & ~0x8000;
	
	if(alt)
		return map_alt_key(scan_code);
	
	if(scan_code >= (sizeof keymap / sizeof keymap[0]))
		return 0;

	return keymap[scan_code] & ~0x8000;
}

static unsigned char map_shift_key(int scan_code){	
	if(scan_code >= (sizeof shift_keymap / sizeof shift_keymap[0]))
		return 0;

	return shift_keymap[scan_code]; 
}

static unsigned char map_alt_key(int scan_code){
	if(scan_code >= (sizeof alt_keymap / sizeof alt_keymap[0]))
		return 0;

	return alt_keymap[scan_code];
}

static void read_char(tty_t* tp, unsigned char c){
	*tp->read_q.head++ = c;
	if(tp->read_q.head == &tp->read_q.buffer[TTY_BUFFER_SIZE])
		tp->read_q.head = tp->read_q.buffer;

	tp->read_q.count++;
}

static int set_special_key_state(int scan_code){
	if(set_shift_key_state(scan_code))
		return 1;

	if(set_alt_key_state(scan_code))
		return 1;

	return 0;
}

static int set_shift_key_state(int scan_code){
	if(scan_code == 0x2a||scan_code == 0x36){
		shift = 1;
		return 1;
	}
	else if(scan_code == 0xaa||scan_code == 0xb6){
		shift = 0;
		return 1;
	}
	return 0;
}

static int set_alt_key_state(int scan_code){
	if(scan_code == 0x38){
		alt = 1;
		return 1;
	}
	else if(scan_code == 0xa6){
		alt = 0;
		return 1;
	}
	return 0;
}

