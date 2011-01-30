/*
   *
   *	tty.c - terminal driver which will be expanded later on
   *			for now just write chars from read_q to write_q and put to screen
   *
   *	Jani Arvonen 2011
*/


#include "kernel.h"
#include <janix/tty.h>

static tty_t tty;
static tty_t* current_tty = NULL;

static void write_to_console(tty_t* tty);
static int is_empty_queue(tty_queue_t* queue);

void init_tty(void){

	tty_t* tp = &tty;
	tp->read_q.count = 0;
	tp->read_q.tail = tp->read_q.head = &tp->read_q.buffer[0];

	tp->write_q.count = 0;
	tp->write_q.tail = tp->write_q.head = &tp->write_q.buffer[0];

	init_screen(tp);
	init_keyboard(tp);	
	current_tty = tp;
}

void tty_interrupt(void){

	if(current_tty == NULL)
		return;

	(*current_tty->dev_read)(current_tty);
	write_to_console(current_tty);
}

void put_to_queue(tty_queue_t* queue, char c){
	*queue->head++ = c;
	if(queue->head == &queue->buffer[TTY_BUFFER_SIZE]){
		queue->head = queue->buffer;
	}
	queue->count++;
}

void get_from_queue(tty_queue_t* queue, char* c){
	*c = *queue->tail++;
	if(queue->tail == &queue->buffer[TTY_BUFFER_SIZE]){
		queue->tail = queue->buffer;
	}
	queue->count--;
}

static void write_to_console(tty_t* tty){

	char c;
	while(!is_empty_queue(&tty->read_q)){
		get_from_queue(&tty->read_q, &c);	
		put_to_queue(&tty->write_q, c);
		tty->dev_write(tty);
	}
}

static int is_empty_queue(tty_queue_t* queue){
	if(queue->head == queue->tail)
		return 1;
	return 0;
}


