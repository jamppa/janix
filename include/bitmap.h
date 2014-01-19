#ifndef _BITMAP_H_
#define _BITMAP_H_

#include <sys/types.h>

typedef struct bitmap_entry {
    u32_t* bitmap;
    u32_t index;
    u32_t offset;
} bitmap_entry_t;

extern u32_t* new_bitmap(size_t size);
extern void set_bitmap_bit(bitmap_entry_t* entry);
extern void clear_bitmap_bit(bitmap_entry_t* entry);
extern int test_bitmap_bit(bitmap_entry_t* entry);
extern bitmap_entry_t first_free_bit(u32_t* bitmap, size_t bitmap_size);

#endif
