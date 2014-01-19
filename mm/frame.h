#ifndef _FRAME_H_
#define _FRAME_H_

#include <sys/types.h>

extern void init_frame_allocator(u32_t memory_size, u32_t page_size);
extern int alloc_frame();
extern void free_frame();

#endif