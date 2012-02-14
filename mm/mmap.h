#ifndef MMAP_H_
#define MMAP_H_

#include <sys/types.h>

extern void init_mmap(u32_t memory_size);
extern void set_mmap_bit(u32_t memory_address);
extern void clear_mmap_bit(u32_t memory_address);
extern int test_mmap_bit(u32_t memory_address);
extern u32_t indexify_address(u32_t memory_address);
extern int first_free_frame();

#endif
