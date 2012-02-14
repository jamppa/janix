/*
   *
   *	mmap.c - memory (bit) map functions
   *
   *	Jani Arvonen 2011
 */

#include <janix/kmalloc.h>
#include <string.h>
#include <sys/types.h>
#include "page.h"
#include "mmap.h"

static u32_t* mmap = NULL; 
static int page_frames = 0;

#define GET_PAGE_FRAME(memory_address)	(memory_address/PAGE_SIZE)
#define GET_MMAP_INDEX(page_frame)	(page_frame/32)
#define GET_MMAP_OFFSET(page_frame)	(page_frame%32)

static int has_free_frames(int mmap_idx);

void init_mmap(u32_t memory_size) {
	page_frames = memory_size/PAGE_SIZE;	
	mmap = (u32_t *)kmalloc(page_frames/32); 
	memset(mmap, 0, page_frames/32);	
}

void set_mmap_bit(u32_t memory_address) {
	if(mmap){
		u32_t page_frame = GET_PAGE_FRAME(memory_address);
		mmap[GET_MMAP_INDEX(page_frame)] |= (0x1 << GET_MMAP_OFFSET(page_frame));
	}
}

void clear_mmap_bit(u32_t memory_address) {
	if(mmap){
		u32_t page_frame = GET_PAGE_FRAME(memory_address);
		mmap[GET_MMAP_INDEX(page_frame)] &= ~(0x1 << GET_MMAP_OFFSET(page_frame));
	}
}

int test_mmap_bit(u32_t memory_address) {
	if(mmap){
		u32_t page_frame = GET_PAGE_FRAME(memory_address);
		return mmap[GET_MMAP_INDEX(page_frame)] & (0x1 << GET_MMAP_OFFSET(page_frame));
	}
	return 0;
}

u32_t indexify_address(u32_t address) {
    return GET_PAGE_FRAME(address);
}

int first_free_frame() {
    int i, n;
    for(i = 0; i < GET_MMAP_INDEX(page_frames); i++) {
        if(has_free_frames(i)){
           for(n = 0; n < 32; n++) {
                if(!(mmap[i] & (0x1 << n))) {
                    return i * 32 + n;
                }
           }
        }
    }
    return -1;
}

int has_free_frames(int mmap_idx) {
    if(mmap != NULL) {
        return mmap[mmap_idx] != 0xffffffff;
    }
    return 0;
}

