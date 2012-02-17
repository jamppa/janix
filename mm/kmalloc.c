/*
   *
   *	kmalloc.c	-	simple memory allocation functions.
   *	
   *	Jani Arvonen 2011
 */

#include <janix/kmalloc.h>
#include <sys/types.h>

// this is defined in linker script
extern int kernel_end;
u32_t free_mem_base = (u32_t)&kernel_end;

static void align_address(u32_t* address);
static u32_t do_alloc(u32_t* address, size_t size);

void* kmalloc(size_t size){
	align_address(&free_mem_base);
	return (void *)do_alloc(&free_mem_base, size);
}

void* kmalloc_p(size_t size, u32_t* phys_addr){
	align_address(&free_mem_base);
	if(phys_addr){
		*phys_addr = free_mem_base;
	}
	return (void *)do_alloc(&free_mem_base, size);
}

static void align_address(u32_t* address){
    if(*address & 0xfffff000){
        *address &= 0xfffff000;
	    *address += 0x1000;
    }
}

static u32_t do_alloc(u32_t* address, size_t size){
	u32_t ret = *address;
	*address += size;
	return ret;
}

