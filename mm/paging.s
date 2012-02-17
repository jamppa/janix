; low-level code for paging
; enable paging and load page directory
; - Jani Arvonen 2012

[bits 32]
[global enable_paging]

[section .text]

enable_paging:

    push eax
    mov eax, [esp + 8]
    mov cr3, eax

    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax            ; enable paging! :)

    pop eax
    ret
