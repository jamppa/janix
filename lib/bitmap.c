#include <janix/kmalloc.h>
#include <sys/types.h>
#include <string.h>
#include <bitmap.h>

static int has_free_bits_in_index(u32_t* bitmap, u32_t idx);
static bitmap_entry_t new_bitmap_entry(u32_t* bitmap, u32_t idx, u32_t offset);

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

bitmap_entry_t first_free_bit(u32_t* bitmap, size_t length) {
    int i, n;
    for(i = 0; i < length; i++) {
        if(has_free_bits_in_index(bitmap, i)){
           for(n = 0; n < 32; n++) {
                if(!(bitmap[i] & (0x1 << n))) {
                    return new_bitmap_entry(bitmap, i, n);
                }
           }
        }
    }
    return new_bitmap_entry(0, 0, 0);
}

static bitmap_entry_t new_bitmap_entry(u32_t* bitmap, u32_t idx, u32_t offset) {
    return (bitmap_entry_t) {
        .bitmap = bitmap,
        .index = idx,
        .offset = offset
    };
}

static int has_free_bits_in_index(u32_t* bitmap, u32_t idx) {
    if(bitmap) {
        return (bitmap[idx] != 0xffffffff);
    }
    return 0;
}