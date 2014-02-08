#include "kernel.h"

#define NUM_OF_GDT_DESCRIPTORS  5

gdt_t gdt;
gdt_descriptor_t gdt_descriptors[NUM_OF_GDT_DESCRIPTORS];

static void setup_gdt(gdt_t* gdt, u32_t descriptors_address);
static void setup_gdt_descriptors(gdt_descriptor_t* descriptors);

static gdt_descriptor_t gdt_null_descriptor();
static gdt_descriptor_t gdt_descriptor(u32_t base, u32_t size, u8_t access);

void init_gdt() {
    setup_gdt(&gdt, (u32_t)&gdt_descriptors);
    setup_gdt_descriptors(gdt_descriptors);
    load_gdt((u32_t)&gdt);
}

static void setup_gdt(gdt_t* gdt, u32_t descriptors_address) {
    gdt->size = (sizeof(gdt_descriptor_t) * (NUM_OF_GDT_DESCRIPTORS - 1));
    gdt->address = descriptors_address;
}

static void setup_gdt_descriptors(gdt_descriptor_t* descriptors) {
    descriptors[0] = gdt_null_descriptor();
    descriptors[1] = gdt_descriptor(0x0, 0xffffffff, 0x9a);
    descriptors[2] = gdt_descriptor(0x0, 0xffffffff, 0x92);
    descriptors[3] = gdt_descriptor(0x0, 0xffffffff, 0xfa);
    descriptors[4] = gdt_descriptor(0x0, 0xffffffff, 0xf2);
}

static gdt_descriptor_t gdt_null_descriptor() {
    return (gdt_descriptor_t) {
        .size_low = 0,
        .base_low = 0,
        .base_middle = 0, 
        .access = 0,
        .granularity = 0,
        .base_high = 0
    };
}

static gdt_descriptor_t gdt_descriptor(u32_t base, u32_t size, u8_t access) {
    return (gdt_descriptor_t) {
        .size_low = (size & 0xffff),
        .base_low = (base & 0xffff),
        .base_middle = ((base >> 16) & 0xff),
        .base_high = ((base >> 24) & 0xff),
        .granularity = 0b11001111,
        .access = access
    };
}