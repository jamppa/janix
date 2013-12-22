#ifndef _GDT_H_
#define _GDT_H_

typedef struct gdt_descriptor {
    u16_t size_low;
    u16_t base_low;
    u8_t base_middle;
    u8_t access;
    u8_t granularity;
    u8_t base_high;
} __attribute__((packed)) gdt_descriptor_t;

typedef struct gdt {
    u16_t size;
    u32_t address; 
} __attribute__((packed)) gdt_t;

#endif