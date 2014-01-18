#include <janix/kmalloc.h>
#include <sys/types.h>
#include <string.h>
#include <bitmap.h>

u32_t* new_bitmap(size_t size) {
    u32_t* map = (u32_t *) kmalloc(size); 
    memset(map, 0, size);
    return map;
}

void set_bitmap_bit(bitmap_entry_t* entry) {
    if(entry && entry->bitmap) {
        entry->bitmap[entry->index] |= (0x1 << entry->offset);
    }
}

void clear_bitmap_bit(bitmap_entry_t* entry) {
    if(entry && entry->bitmap) {
        entry->bitmap[entry->index] &= ~(0x1 << entry->offset);   
    }
}

int test_bitmap_bit(bitmap_entry_t* entry) {
    if(entry && entry->bitmap) {
        return entry->bitmap[entry->index] & (0x1 << entry->offset);
    }
    return 0;
}