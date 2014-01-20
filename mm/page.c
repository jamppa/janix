#include <sys/types.h>
#include <janix/kmalloc.h>
#include "../kernel/kernel.h"
#include "page.h"

extern void enable_paging(u32_t ptt_address);
extern u32_t get_fault_page_address();

static page_directory_t* kernel_pd = NULL;
static page_directory_t* alloc_pd(void);

static int has_page_table(u32_t address, page_directory_t* ptt);
static void identity_map_kernel(page_directory_t* ptt);
static void alloc_kernel_page_table(u32_t address, page_directory_t* ptt);
static void alloc_kernel_page(page_t* page);
static void init_kernel_page(page_t* page, u32_t frame_addr);
static void pagefault_handler(registers_t regs);

static u32_t memory_addr_to_page_table(u32_t memory_addr);
static u32_t memory_addr_to_page(u32_t memory_addr);

void init_paging(void) {

    init_frame_allocator(MEMORY_SIZE, PAGE_SIZE);
	kernel_pd = alloc_pd();
    identity_map_kernel(kernel_pd);
    
    register_interrupt_handler(PAGE_FAULT_INT, pagefault_handler);
    load_page_directory(kernel_pd);
}

void load_page_directory(page_directory_t* ptt) {
    u32_t ptt_addr = (u32_t)&ptt->page_tables_physical;
    enable_paging(ptt_addr);
}

page_t* get_page(u32_t memory_address, page_directory_t* pd) {
    u32_t page_table = memory_addr_to_page_table(memory_address);
    u32_t page = memory_addr_to_page(memory_address);
    return &pd->page_tables[page_table]->pages[page];
}

static void alloc_kernel_page_table(u32_t address, page_directory_t* pd) {
    u32_t memory_addr_phys = 0;
    u32_t page_table = memory_addr_to_page_table(address);
    pd->page_tables[page_table] = 
        (page_table_t *) kmalloc_p(sizeof(page_table_t), &memory_addr_phys);
    memset(pd->page_tables[page_table], 0, sizeof(page_table_t));
    pd->page_tables_physical[page_table] = memory_addr_phys | 0x7;
}

static void alloc_kernel_page(page_t* page) {
    if(page != NULL && page->frame_addr == 0) {
        int frame_addr = alloc_frame();
        if(frame_addr == -1){
            panic("no free frames!");
        }
        init_kernel_page(page, frame_addr);
    }
}

static void identity_map_kernel(page_directory_t* ptt) {
    u32_t current_address = 0x0;
    while(current_address < free_mem_base){
       if(!has_page_table(current_address, ptt)) {
           alloc_kernel_page_table(current_address, ptt);
       }
       page_t* page = get_page(current_address, ptt);
       alloc_kernel_page(page);
       current_address += PAGE_SIZE;
    }
}

static int has_page_table(u32_t address, page_directory_t* pd) {
    if(pd->page_tables[memory_addr_to_page_table(address)]){
        return 1;
    }
    return 0;
}

static page_directory_t* alloc_pd() {
	page_directory_t* ptt = (page_directory_t *)kmalloc(sizeof(page_directory_t)); 
	memset(ptt, 0, sizeof(*ptt));
	return ptt;
}

static void init_kernel_page(page_t* page, u32_t frame_addr) {
    if(page){
        page->is_present = 1;
        page->read_write = 1;
        page->is_user = 0;
        page->frame_addr = frame_addr;
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

static u32_t memory_addr_to_page_table(u32_t memory_addr) {
    return memory_addr_to_frame_addr(memory_addr) / 1024;
}

static u32_t memory_addr_to_page(u32_t memory_addr) {
    return memory_addr_to_frame_addr(memory_addr) % 1024;
}
