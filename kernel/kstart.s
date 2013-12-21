[bits 32]

[extern kernel_main]
[global kernel_start]
[global load_idt]

MODULEALIGN equ  1<<0                   ; align loaded modules on page boundaries
MEMINFO     equ  1<<1                   ; provide memory map
FLAGS       equ  MODULEALIGN | MEMINFO  ; this is the Multiboot 'flag' field
MAGIC       equ    0x1BADB002           ; 'magic number' lets bootloader find the header
CHECKSUM    equ -(MAGIC + FLAGS)        ; checksum required

[section .text]
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

kernel_start:    	
    call kernel_main

hang:	
    jmp hang

load_idt:					
	mov eax, [esp+4]
	lidt [eax]
	sti
	ret
	
