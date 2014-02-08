[bits 32]

[extern kernel_main]
[extern code]
[extern bss]
[extern kernel_end]
[global kernel_start]
[global mboot]

MODULEALIGN equ  1<<0                   ; align loaded modules on page boundaries
MEMINFO     equ  1<<1                   ; provide memory map
FLAGS       equ  MODULEALIGN | MEMINFO  ; this is the Multiboot 'flag' field
MAGIC       equ    0x1BADB002           ; 'magic number' lets bootloader find the header
CHECKSUM    equ -(MAGIC + FLAGS)        ; checksum required

mboot:
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

    dd mboot
    dd code
    dd bss
    dd kernel_end
    dd kernel_start

kernel_start:
    cli
    push ebx    	
    call kernel_main
    cli
    hlt

hang:	
    jmp hang
