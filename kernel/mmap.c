#include "mmap.h"

static int is_mmap_available(const multiboot_info_t* mb);
static int get_memory_size(const multiboot_info_t* mb);

static mmap_t new_mmap();

mmap_t get_mmap(const multiboot_info_t* mb) {
    mmap_t mmap = new_mmap();
    if(is_mmap_available(mb)) {
        mmap.is_available = 1;
        mmap.mem_size = get_memory_size(mb);
    }
    return mmap;
}

static int get_memory_size(const multiboot_info_t* mb) {
    return mb->mem_upper;
}

static mmap_t new_mmap() {
    return (mmap_t) {
        .is_available = 0,
        .mem_size = 0
    };
}

static int is_mmap_available(const multiboot_info_t* mb) {
    return mb->flags & 0x01;
}

