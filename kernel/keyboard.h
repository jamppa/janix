#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#define KEYBOARD_IO					0x60
#define KEYBOARD_ACK_BIT			0x80
#define PPI_PORT_B					0x61

#define KEYBOARD_BUFFER_SIZE		32

typedef struct kb_t {

	int buffer_count;
	char buffer[KEYBOARD_BUFFER_SIZE];

	char* buffer_head;
	char* buffer_tail;

} keyboard_t;

extern void init_keyboard();

#endif
