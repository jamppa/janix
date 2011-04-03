#ifndef KMALLOC_H_
#define KMALLOC_H_

#include <sys/types.h>

extern void* kmalloc(size_t size);
extern void* kmalloc_p(size_t size, u32_t* phys_addr);

#endif
