#include <sys/types.h>
#include <bitmap.h>
#include "frame.h"

static u32_t num_of_page_frames = 0;
static u32_t memory_bitmap_size = 0;
static u32_t* memory_bitmap = NULL;

static u32_t frame_addr(bitmap_entry_t* entry);
static u32_t frame_addr_to_mmap_index(u32_t frame_addr);
static u32_t frame_addr_to_mmap_offset(u32_t frame_addr);

void init_frame_allocator(u32_t memory_size, u32_t page_size) {
    num_of_page_frames = memory_size / page_size;
    memory_bitmap_size = num_of_page_frames / 32;
    memory_bitmap = (u32_t *) new_bitmap(memory_bitmap_size * sizeof(u32_t));
}

int alloc_frame() {
    if(memory_bitmap){
        bitmap_entry_t entry = first_free_bit(memory_bitmap, memory_bitmap_size);
        if(entry.bitmap) {
            set_bitmap_bit(&entry);
            return frame_addr(&entry);
        }
    }
    return -1;
}

void free_frame(u32_t frame_addr) {
    bitmap_entry_t entry = new_bitmap_entry(
        memory_bitmap, frame_addr_to_mmap_index(frame_addr), frame_addr_to_mmap_offset(frame_addr));
    clear_bitmap_bit(&entry);
}

static u32_t frame_addr(bitmap_entry_t* entry) {
    return entry->index * 32 + entry->offset;
}

static u32_t frame_addr_to_mmap_index(u32_t frame_addr) {
    return frame_addr / 32;
}

static u32_t frame_addr_to_mmap_offset(u32_t frame_addr) {
    return frame_addr % 32;
}