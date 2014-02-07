#include "kernel.h"

void out_byte(u16_t port, u8_t value){
	asm volatile ("outb %1, %0": : "dN" (port), "a" (value));
}

u8_t in_byte(u16_t port){

	u8_t byte_read = 0;
	asm volatile ("inb %1, %0" : "=a" (byte_read) : "dN" (port));
	return byte_read;
}

u16_t in_word(u16_t port){
	
	u16_t word_read = 0;
	asm volatile ("inw %1, %0" : "=a" (word_read) : "dN" (port));
	return word_read;
}

