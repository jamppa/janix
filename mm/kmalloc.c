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
int freebase = (int)&kernel_end;

static void align_address(int* address);
static u32_t do_alloc(int* address, size_t size);

void* kmalloc(size_t size){

	align_address(&freebase);
	return (void *)do_alloc(&freebase, size);
}

void* kmalloc_p(size_t size, u32_t* phys_addr){

	align_address(&freebase);
	if(phys_addr){
		*phys_addr = freebase;
	}
	return (void *)do_alloc(&freebase, size);
}

static void align_address(int* address){
	*address &= 0xfffff000;
	*address += 0x1000;
}

static u32_t do_alloc(int* address, size_t size){
	
	u32_t ret = *address;
	*address += size;

	return ret;
}




