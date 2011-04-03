; small bootloader or MBR for janix (NASM)
;
; Jani Arvonen - 2010

[bits 16]
[org 0x7c00]

[global KERNEL_CODE]
[global KERNEL_DATA]

		xor ax, ax						; datasegments to 0x0000
		mov ds, ax
		mov es, ax
		mov [boot_drive], dl
		mov si, msg
		call print
		call get_memory
		jmp load_kernel
halt:
		hlt
		jmp halt

get_memory:

		xor ax, ax
		mov ah, 0x88
		int 0x15
		mov [extended_memory], ax
		ret

print:
		mov al, [si]
		or al, al
		jz exit_print
		mov ah, 0x0e
		mov bh, 0x00
		mov bl, 0x07
		int 0x10
		inc si
		jmp print
		exit_print:
		ret

load_kernel:

		mov ah, 0x02					; read sectors from drive
		mov al, 20						; lets read 20 blocks = 512 * 20 = ~10k	
		mov ch, 0x00
		mov cl, 0x02					; from 2. sector
		mov dh, 0x00
		mov bx, 0x0ffff					; where to read = 0xffff0:0x10 ~ 1MB. Note real mode segmentation
		mov es, bx
		mov bx, 0x10
		int 0x13						; fire the interrupt
		jnc boot_kernel
		jmp $							; hang if fails

boot_kernel:
		cli							; disable interrupts
		lgdt [gdt_desc]				; load GDT
		lidt [idt_desc]				; load IDT
		mov eax, cr0
		or eax, 1					; set lowest bit
		mov cr0, eax				; here it goes! see you in procted mode

		mov eax, cr4
		or eax, 16					; set fifth bit (PAE Physical Address Extension)
		mov cr4, eax
		jmp KERNEL_CODE:kernel_32	; long jump to 32-bit kernel code

[bits 32]

kernel_32:

		mov eax, KERNEL_DATA
		mov ds, eax
		mov es, eax
		mov fs, eax
		mov gs, eax
		mov ss, eax
		mov esp, 0x00040000			; stack pointer at 0x00040000, so stack size is 256k
		call check_a20
		jmp KERNEL_CODE:0x100000
	
check_a20:							; enable line a20 - this is from some old linux

		push eax
        push ebx
        mov word [0x7dfe], 0xaa55
        mov word [0x107dfe], 0x0000
        mov word ax, [0x7dfe]
        cmp ax, 0xaa55
        je a20_is_enabled
        call a20_enable
        jmp check_a20
        a20_is_enabled:
        pop ebx
        pop eax
        ret

empty_8042:
        in al, 0x64             ; 8042 status port
        test al, 2              ; is input buffer full?
        jnz empty_8042          ; yes, loop
        ret

empty_8042_2:
        in al, 0x64             ; 8042 status port
        test al, 1              ; is input buffer full?
        jnz empty_8042_2        ; yes, loop
        ret

a20_enable:
        call empty_8042
        mov al, 0xad
        out 0x64, al
        call empty_8042
        mov al, 0xd0
        out 0x64, al
        call empty_8042_2
        in al, 0x60
        push eax
        call empty_8042
        mov al, 0xd1
        out 0x64, al
        call empty_8042
        pop eax
        or al, 2
        out 0x60, al
        call empty_8042
        mov al, 0xae
        out 0x64, al
        call empty_8042
        ret

idt_desc:

		dw 0x0000
		dw 0x0000
		dw 0x0000

gdt:
null_desc:

		dd 0x00000000
		dd 0x00000000

KERNEL_CODE equ $-gdt				; calc dynamically 0x08 for this descriptor
code_desc:

		dw 0xffff					; limit lower 2 bytes
		dw 0x0000					; base address lower 3 bytes		
		db 0x00
		db 10011010b				; present(1), privilege(00), data/code(1), code(1), conform(0), readable(1), access(0)
		db 11001111b				; granularity(1), 32bitsize(1) reserved(0), prog(0), segment limit bits (1111 = 0xf)
		db 0x00						; top base address byte

KERNEL_DATA equ $-gdt				; calc dynamically 0x10 (16d) for this descriptor
data_desc:

		dw 0xffff					; again limit lower 2 bytes
		dw 0x0000 					; base address lower 3 bytes
		db 0x00
		db 10010010b				; same as descriptor for code segment except E bit = 0
		db 11001111b				; same as descriptor for code segment
		db 0x00						; same as descriptor for code segment
gdt_end:

gdt_desc:
		
		dw gdt_end-gdt-1			; two-byte limit
		dd gdt						; four-byte base address of gdt
data:
		msg db 'Booting Janix...',0		; welcome message
		boot_drive db 0x00				; store boot drive here
		extended_memory dw 0x0000		; store extended memory here

		times 510-($-$$) db 0			; fill rest of the bytes
		dw 0xaa55						; signature for MBR (512 bytes ready)

