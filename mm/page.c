/*
   *
   *	page.c	-	routines for paging and frame allocation
   *
   *	Jani Arvonen  2011
 */

#include <string.h>
#include <sys/types.h>
#include <janix/kmalloc.h>
#include "page.h"
#include "mmap.h"

extern int freebase;

static page_table_table_t* kernel_ptt = NULL;
static page_table_table_t* alloc_ptt(void);

void init_paging(void) {
	
	init_mmap(MEMORY_SIZE);
	kernel_ptt = alloc_ptt();
	
	//TODO: continue here by mapping physical memory to virtual addr
}

void load_page_table_table(page_table_table_t* ptt) {

}

page_t* get_page(u32_t memory_address, page_table_table_t* ptt) {
	return NULL;
}

static page_table_table_t* alloc_ptt(void) {

	page_table_table_t* ptt = (page_table_table_t *)kmalloc(sizeof(page_table_table_t)); 
	memset(ptt, 0, sizeof(*ptt));

	return ptt;
}


