#ifndef PAGE_H_
#define PAGE_H_

#include <sys/types.h>

#define	MEMORY_SIZE		0x2000000		// for now, lets assume it is ~32MB
#define PAGE_SIZE		0x1000			// page size is 4KB

typedef struct page {
	
	u32_t is_present	: 1;
	u32_t read_write	: 1;
	u32_t is_user		: 1;
	u32_t is_accessed	: 1;
	u32_t is_dirty		: 1;
	u32_t not_used		: 7;
	u32_t frame_addr	: 20;

} page_t;

typedef struct page_table {
	page_t pages[1024];
} page_table_t;

typedef struct page_table_table {

	page_table_t* page_tables[1024];
	u32_t page_tables_physical[1024];

} page_table_table_t;

extern void init_paging(void);
extern void load_page_table_table(page_table_table_t* ptt);
extern page_t* get_page(u32_t address, page_table_table_t* ptt);

#endif
