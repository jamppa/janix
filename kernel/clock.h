#ifndef _CLOCK_H_
#define _CLOCK_H_

#define	TIMER_FREQUENCY		1193180
#define HZ					100
#define TIMER_DIV			((unsigned)(TIMER_FREQUENCY/HZ))			

#define TIMER_DATA_PORT		0x40
#define TIMER_CMD_PORT		0x43
#define TIMER_REPEAT_MODE	0x36

extern void init_clock(void);

#endif
