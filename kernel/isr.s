; isr.s -	contains interrupt service routines which are called
;			when interrupt arrives (cpu dedicated or from PIC)
;
;			Jani Arvonen 2010

[extern isr_handler]			; upper lever ISR handler which is called from here
[extern irq_handler]			; upper level IRQ handler
[global sti]
[global cli]
[global hlt]

; Two macros for ISR stubs. We're lazy and dont want to write duplicate code
; ISR_WITH_ERRCODE is meant to be used with isr's which report the error code
; ISR_WITHOUT_ERRCODE is meant to be used with isr's that doesn't report error code

%macro ISR_WITH_ERRCODE 1
	[global isr_%1]
	
	isr_%1:
		cli
		push byte %1			; push the interrupt number
		jmp isr_common			; jump to the common stub
%endmacro


%macro ISR_WITHOUT_ERRCODE 1
	[global isr_%1]

	isr_%1:
		cli
		push byte 0				; push dummy errorcode
		push byte %1
		jmp isr_common
%endmacro

%macro IRQ 2					; 2 params: 1 - irq number, 2 - isr number
	[global irq_%1]

	irq_%1:
		cli
		push byte 0				; push dummy errorcode
		push byte %2			; push isr number
		jmp irq_common
%endmacro

;	Interrupt Service Routines

ISR_WITHOUT_ERRCODE 0
ISR_WITHOUT_ERRCODE 1
ISR_WITHOUT_ERRCODE 2
ISR_WITHOUT_ERRCODE 3
ISR_WITHOUT_ERRCODE 4
ISR_WITHOUT_ERRCODE 5
ISR_WITHOUT_ERRCODE 6
ISR_WITHOUT_ERRCODE 7
ISR_WITH_ERRCODE	8
ISR_WITHOUT_ERRCODE 9
ISR_WITH_ERRCODE	10
ISR_WITH_ERRCODE	11
ISR_WITH_ERRCODE	12
ISR_WITH_ERRCODE	13
ISR_WITH_ERRCODE	14
ISR_WITHOUT_ERRCODE 15
ISR_WITHOUT_ERRCODE 16
ISR_WITHOUT_ERRCODE 17
ISR_WITHOUT_ERRCODE 18
ISR_WITHOUT_ERRCODE 19
ISR_WITHOUT_ERRCODE 20
ISR_WITHOUT_ERRCODE 21
ISR_WITHOUT_ERRCODE 22
ISR_WITHOUT_ERRCODE 23
ISR_WITHOUT_ERRCODE 24
ISR_WITHOUT_ERRCODE 25
ISR_WITHOUT_ERRCODE 26
ISR_WITHOUT_ERRCODE 27
ISR_WITHOUT_ERRCODE 28
ISR_WITHOUT_ERRCODE 29
ISR_WITHOUT_ERRCODE 30
ISR_WITHOUT_ERRCODE 31

; IRQ service routines

IRQ	0,	32
IRQ 1,	33
IRQ 2,	34
IRQ 3,	35
IRQ 4,	36
IRQ	5,	37
IRQ 6,	38
IRQ	7,	39
IRQ	8,	40
IRQ	9,	41
IRQ	10,	42
IRQ	11,	43
IRQ 12,	44
IRQ	13,	45
IRQ	14,	46
IRQ	15,	47

isr_common:

	pusha					; push all (eax, ebx etc.) registers into stack

	mov ax, ds				; save current data segment descriptor
	push eax

	mov ax, 0x10			; load the kernel data descriptor
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	call isr_handler		; now handle the interrupt by calling the handler

	pop ebx					; reload original data segment descriptor
	mov ds, bx
	mov es, bx
	mov fs, bx
	mov gs, bx

	popa					; pop all (eax, ebx etc.) registers from stack
	add esp, 8				; clean stack from pushed error code and interrupt number
	sti
	iret

; do same tricks that our "isr_common" except call irq_handler
irq_common:					 

	pusha

	mov ax, ds
	push eax

	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	call irq_handler

	pop ebx
	mov ds, bx
	mov es, bx
	mov fs, bx
	mov gs, bx

	popa
	add esp, 8
	sti
	iret

sti:
    sti
    ret

cli:
    cli
    ret

hlt:
    hlt
    ret
