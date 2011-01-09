#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#define VIDEO_MEMORY_BASE	0xb8000
#define VIDEO_MEMORY_SIZE	0x4000
#define CRTC_6845_PORT_C	0x3d4
#define CRTC_6845_PORT_M	0x3b4
#define CRTC_CURSOR_REG		14
#define VGA_MISC_PORT		0x3cc

#define SCREEN_WIDTH		80
#define SCREEN_HEIGHT		25
#define COLOR_WHITE			15
#define COLOR_BLACK			0
#define BLANK				0x20
#define TAB_MASK			7
#define TAB_SIZE			8

typedef struct console_t {
	
	u16_t* video_memory_addr;
	int crtc_addr;

	int current_y;
	int current_x;
	
	u16_t attribute;
	int console_width;
	int console_height;

} Console;

extern void init_screen(void);
extern void console_putc(Console* console, char c);
extern void console_clear(Console* console);
extern void console_puts(Console* console, char* str);

extern void putk(char c);
extern void putsk(char* str);
extern void h_putsk(u32_t num);
extern void clear(void);

#endif
