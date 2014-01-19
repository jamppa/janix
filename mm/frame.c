#include <sys/types.h>
#include <bitmap.h>
#include "frame.h"

static u32_t num_of_page_frames = 0;
static u32_t memory_bitmap_size = 0;
static u32_t* memory_bitmap = NULL;

void init_frame_allocator(u32_t memory_size, u32_t page_size) {
    num_of_page_frames = memory_size / page_size;
    memory_bitmap_size = num_of_page_frames / 32;
    memory_bitmap = (u32_t *) new_bitmap(memory_bitmap_size * sizeof(u32_t));
}
