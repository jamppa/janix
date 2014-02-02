#ifndef KHEAP_H_
#define KHEAP_H_

#include <sys/types.h>

#define KHEAP_START     0xC0000000
#define KHEAP_END       0xCFFFF000

typedef struct heap {
    u32_t start_addr;
    u32_t current_addr;
    u32_t end_addr;
} heap_t;

extern heap_t* init_kernel_heap(void);

#endif