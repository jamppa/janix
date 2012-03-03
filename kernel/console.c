/*
   *
   *	implementation of a simple console driver
   * 
   * 	Jani Arvonen 2010
 */

#include "kernel.h"
#include <janix/tty.h>

static console_t console; 
static console_t* current_console = (void *)0;

static const char* hex_array = "0123456789abcdef";

static void write_console(tty_t* tty);
static u16_t get_current_cursor_location(console_t* console);
static void move_cursor(console_t* console);
static void scroll_console(console_t* console);
static u8_t need_for_scroll(console_t* console);
static void move_lines_by_one(console_t* console);
static void blank_bottom_line(console_t* console);
static void handle_special_char(console_t* console, char c);


void putk(char c){
	if(c != 0){
		console_putc(current_console, c);
	}
}

void putsk(const char* str){
	if(str){
		console_puts(current_console, str);
	}
}

void puthk(u32_t num){

	int i;
	for(i = 28; i >= 0; i -= 4){
		if(i == 28)
			putsk("0x");
		putk(hex_array[(num >> i) & 0xf]);
	}
}

void clear(void){
	console_clear(current_console);
}

void init_screen(tty_t* tp){

	console.video_memory_addr = (u16_t *)VIDEO_MEMORY_BASE;
	if((in_word(VGA_MISC_PORT) & 0x1) != 0){
		console.crtc_addr = CRTC_6845_PORT_C;
	}
	else{
		console.crtc_addr = CRTC_6845_PORT_M; 
	}

	console.current_y = 0;
	console.current_x = 0;
	console.console_width = SCREEN_WIDTH;
	console.console_height = SCREEN_HEIGHT;

	u8_t background_color = COLOR_BLACK;
	u8_t foreground_color = COLOR_WHITE;
	u8_t attribute_byte = (background_color << 4)|(foreground_color & 0xf); // OR these 2
	console.attribute = attribute_byte << 8;	// lower 8-bit for character

	current_console = &console;
	tp->console = current_console;
	tp->dev_write = write_console;
}

void console_putc(console_t* console, char c){

	u16_t* char_location;
	handle_special_char(console, c);

	// handle printable character
	if(c >= ' '){
		char_location = console->video_memory_addr + 
			(console->current_y * console->console_width) + console->current_x;
		*char_location = c|console->attribute;
		console->current_x++;
	}

	if(console->current_x >= console->console_width){
		console->current_x = 0;
		console->current_y++;
	}

	scroll_console(console);
	move_cursor(console);
}

void console_clear(console_t* console){
	
	int i;
	u16_t blank = BLANK|console->attribute;
	for(i = 0; i < console->console_width * console->console_height; i++){
		console->video_memory_addr[i] = blank; 
	}

	console->current_x = 0;
	console->current_y = 0;
	move_cursor(console);
}

void console_puts(console_t* console, const char* str){
	while(*str){
		console_putc(console, *str++);
	}
}	

static void write_console(tty_t* tty){
	tty_queue_t* queue = &tty->write_q;
	char c;
	while(queue->count){
		get_from_queue(queue, &c);
		console_putc(tty->console, c);	
	}
}

static void handle_special_char(console_t* console, char c){

	if(c == 0x08 && console->current_x){	/*backspace*/
		console->current_x--;
	}
	else if(c == 0x09){ 					/*tab - */
		console->current_x = (console->current_x + TAB_SIZE) & ~TAB_MASK;
	}
	else if(c == '\r'){
		console->current_x = 0;
	}
	else if(c == '\n'){
		console->current_x = 0;
		console->current_y++;
	}
}

static void move_cursor(console_t* console){

	u16_t cursor_location = get_current_cursor_location(console);
	out_byte(console->crtc_addr, CRTC_CURSOR_REG);
	out_byte(console->crtc_addr + 1, cursor_location >> 8);
	out_byte(console->crtc_addr, CRTC_CURSOR_REG + 1);
	out_byte(console->crtc_addr + 1, cursor_location);
}

static void scroll_console(console_t* console){
 
	if(need_for_scroll(console)){
		move_lines_by_one(console);	
		blank_bottom_line(console);
		console->current_y = console->console_height-1;	
	}
}

static void blank_bottom_line(console_t* console){
	
	u16_t blank = BLANK|(console->attribute); 
	int i;
	for(i = (console->console_height - 1)*console->console_width;
			i < console->console_width * console->console_height; i++){
		console->video_memory_addr[i] = blank;
	}
}

static void move_lines_by_one(console_t* console){

	int i;
	for(i = 0; i < (console->console_height-1)*console->console_width; i++){
		*(console->video_memory_addr + i) = 
			console->video_memory_addr[i + console->console_width];
	}
}

static u8_t need_for_scroll(console_t* console){
	u8_t is_need = 0;
	if(console->current_y >= console->console_height)
		is_need = 1;

	return is_need;
}

static u16_t get_current_cursor_location(console_t* console){
	return (console->current_y * console->console_width + console->current_x);
}	
