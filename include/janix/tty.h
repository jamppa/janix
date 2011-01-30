#ifndef _TTY_H_
#define _TTY_H_

#define TTY_BUFFER_SIZE			1024

#include <janix/console.h>

typedef struct tty_queue {

	int count;
	char* tail;
	char* head;
	char buffer[TTY_BUFFER_SIZE];

} tty_queue_t;

extern void put_to_queue(tty_queue_t* queue, char c);
extern void get_from_queue(tty_queue_t* queue, char* c);

typedef struct tty {

	void (*dev_read)(struct tty* tty);
	void (*dev_write)(struct tty* tty);
	tty_queue_t read_q;
	tty_queue_t write_q;	

	console_t* console;

} tty_t;

extern void init_tty(void);
extern void tty_interrupt(void);
extern void init_screen(tty_t* tp);

#endif 

