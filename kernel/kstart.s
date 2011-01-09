; kstart.asm - call to kernels main c function
;
; Jani Arvonen 2010

[bits 32]

[extern kernel_main]
[global kernel_start]
[global load_idt]

[section .text]
kernel_start:
		
		call kernel_main				; call the kernel main C function

hang:	jmp hang


load_idt:								; function for loading Interrup Descriptor Table
	mov eax, [esp+4]					; get idt address
	lidt [eax]
	sti
	ret
	
