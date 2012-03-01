; low-level code related to paging
; - Jani Arvonen 2012

[bits 32]
[global enable_paging]
[global get_fault_page_address]

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

get_fault_page_address:
    
    mov eax, 0x0
    mov eax, cr2
    ret
