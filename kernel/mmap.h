#ifndef _MMAP_H_
#define _MMAP_H

typedef struct mmap {
    int is_available;
    unsigned long mem_size;
    unsigned long mem_size_mb;
} mmap_t;

extern mmap_t get_mmap(const multiboot_info_t* mb);

#endif