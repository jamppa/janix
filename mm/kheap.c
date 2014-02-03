#include <sys/types.h>
#include <janix/kmalloc.h>
#include <liballoc.h>
#include "../kernel/kernel.h"
#include "kheap.h"
#include "page.h"
#include "frame.h"

static heap_t *kheap = NULL;
static heap_t* allocate_kernel_heap();

static bool heap_allocable(int num_of_pages);

heap_t* init_kernel_heap() {
    kheap = allocate_kernel_heap();
    return kheap;
}

int liballoc_lock() {
    cli();
    return 0;
}

int liballoc_unlock() {
    sti();
    return 0;
}

void* liballoc_alloc(int num_of_pages) {

    if(!heap_allocable(num_of_pages)){
        return NULL;
    }

    void* current_addr = (void *)kheap->current_addr;
    while(num_of_pages > 0) {
        map_kernel_page(alloc_frame(), kheap->current_addr);
        kheap->current_addr += PAGE_SIZE;
        num_of_pages--;
    }
    return current_addr;
}

int liballoc_free(void* address, int num_of_pages) {
    while(num_of_pages > 0) {
        unmap_kernel_page((u32_t) address);
        address += PAGE_SIZE;
        num_of_pages--;
    }
    return 0;
}

static bool heap_allocable(int num_of_pages) {
    if(kheap == NULL){
        return false;
    }
    if(kheap->current_addr + (num_of_pages * PAGE_SIZE) > kheap->end_addr) {
        return false;
    }
    return true;
}

static heap_t* allocate_kernel_heap() {
    heap_t *heap = (heap_t *) kmalloc(sizeof(heap_t));
    heap->start_addr = KHEAP_START;
    heap->current_addr = KHEAP_START;
    heap->end_addr = KHEAP_END;
    return heap;    
}