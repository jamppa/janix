#include <sys/types.h>
#include <string.h>
#include <bitmap.h>

u32_t* new_bitmap(size_t size) {
    u32_t* map = (u32_t *) kmalloc(size); 
    memset(map, 0, size);
    return map;
}

void set_bitmap_bit(bitmap_entry_t* entry) {

}

void clear_bitmap_bit(bitmap_entry_t* entry) {

}

void test_bitmap_bit(bitmap_entry_t* entry) {
    
}