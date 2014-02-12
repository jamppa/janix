#include "multiboot.h"
#include "mmap.h"

static int is_mmap_available(const multiboot_info_t* mb);
static void init_memory_sizes(const multiboot_info_t* mb, mmap_t* mmap);

static mmap_t new_mmap();

mmap_t get_mmap(const multiboot_info_t* mb) {
    mmap_t mmap = new_mmap();
    if(is_mmap_available(mb)) {
        mmap.is_available = 1;
        init_memory_sizes(mb, &mmap);
    }
    return mmap;
}

static void init_memory_sizes(const multiboot_info_t* mb, mmap_t* mmap) {
    mmap->mem_size = mb->mem_upper;
    mmap->mem_size_mb = (mb->mem_upper / 1024);
}

static mmap_t new_mmap() {
    return (mmap_t) {
        .is_available = 0,
        .mem_size = 0,
        .mem_size_mb = 0
    };
}

static int is_mmap_available(const multiboot_info_t* mb) {
    return mb->flags & 0x01;
}

