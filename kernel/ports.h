#ifndef _PORTS_H_
#define _PORTS_H

/*
   *	functions for low-level I/O port operations.
   *	implemented in ports.c
 */

extern void out_byte(u16_t port, u8_t value);
extern u8_t in_byte(u16_t port);
extern u16_t in_word(u16_t port);

#endif
