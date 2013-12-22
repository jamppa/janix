/*
   *
   *	page.c	-	routines for paging and frame allocation
   *
   *	Jani Arvonen  2011
 */

#include <sys/types.h>
#include <janix/kmalloc.h>
#include "../kernel/kernel.h"

extern int free_mem_base;
extern void enable_paging(u32_t ptt_address);
extern u32_t get_fault_page_address();

static page_table_table_t* current_ptt = NULL;
static page_table_table_t* kernel_ptt = NULL;
static page_table_table_t* alloc_ptt(void);

static int has_page_table(u32_t address, page_table_table_t* ptt);
static void identity_map_kernel(page_table_table_t* ptt);
static void alloc_kernel_page_table(u32_t address, page_table_table_t* ptt);
static void alloc_kernel_page_frame(page_t* page);
static void init_kernel_page(page_t* page, u32_t frame_idx);

static void pagefault_handler(registers_t regs);

void init_paging(void) {

	init_mmap(MEMORY_SIZE);
	kernel_ptt = alloc_ptt();
    identity_map_kernel(kernel_ptt);
    
    register_interrupt_handler(PAGE_FAULT_INT, pagefault_handler);
    load_page_table_table(kernel_ptt);
}

void load_page_table_table(page_table_table_t* ptt) {
    current_ptt = ptt;
    u32_t ptt_addr = (u32_t)&ptt->page_tables_physical;
    enable_paging(ptt_addr);
}

page_t* get_page(u32_t memory_address, page_table_table_t* ptt) {
    u32_t idx = indexify_address(memory_address) / 1024;
    return &ptt->page_tables[idx]->pages[indexify_address(memory_address) % 1024];
}

static void alloc_kernel_page_table(u32_t address, page_table_table_t* ptt) {
    u32_t physical_address = 0;
    u32_t page_table_idx = indexify_address(address) / 1024;
    ptt->page_tables[page_table_idx] = 
        (page_table_t *)kmalloc_p(sizeof(page_table_t), &physical_address);
    memset(ptt->page_tables[page_table_idx], 0, sizeof(page_table_t));
    ptt->page_tables_physical[page_table_idx] = physical_address | 0x7;
}

static void alloc_kernel_page_frame(page_t* page) {
    if(page != NULL && page->frame_addr == 0) {
       int frame_idx = first_free_frame();
       if(frame_idx != -1) {
            set_mmap_bit(frame_idx * PAGE_SIZE);
            init_kernel_page(page, frame_idx);
       }
    }
}

static void identity_map_kernel(page_table_table_t* ptt) {
    u32_t current_address = 0x0;
    while(current_address < free_mem_base){
       if(!has_page_table(current_address, ptt)) {
           alloc_kernel_page_table(current_address, ptt);
       }
       page_t* page = get_page(current_address, ptt);
       alloc_kernel_page_frame(page);
       current_address += PAGE_SIZE;
    }
}

static int has_page_table(u32_t address, page_table_table_t* ptt) {
    if(ptt->page_tables[indexify_address(address) / 1024]){
        return 1;
    }
    return 0;
}

static page_table_table_t* alloc_ptt(void) {
	page_table_table_t* ptt = (page_table_table_t *)kmalloc(sizeof(page_table_table_t)); 
	memset(ptt, 0, sizeof(*ptt));
	return ptt;
}

static void init_kernel_page(page_t* page, u32_t frame_idx) {
    if(page){
        page->is_present = 1;
        page->read_write = 1;
        page->is_user = 0;
        page->frame_addr = frame_idx;
    }
}

static void pagefault_handler(registers_t regs) {
    int fault_address = get_fault_page_address();
    putsk("page fault at: ");
    puthk(fault_address);
    putsk("\npage fault error code: ");
    puthk(regs.error_code);
    die("\n", &regs);
    panic("page fault\n");
}





