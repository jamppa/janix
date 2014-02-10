#ifndef _MMAP_H_
#define _MMAP_H

#include "multiboot.h"

typedef struct mmap {
    int is_available;
    unsigned long mem_size;
} mmap_t;

mmap_t get_mmap(const multiboot_info_t* mb);

#endif