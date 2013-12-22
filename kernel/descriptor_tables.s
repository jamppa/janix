[bits 32]

[global load_gdt]
[global load_idt]

load_idt:                   
    mov eax, [esp + 4]
    lidt [eax]
    ret

load_gdt:
    mov eax, [esp + 4]
    lgdt [eax]

set_segment_registers:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:flush

flush:
    ret