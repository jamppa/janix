/*
   *	intr.c - Interrupt related functions. IDT initialization etc.
   *
   *	Jani Arvonen 2010
 */

#include "kernel.h"

int_handler_t interrupt_handlers[NUM_OF_INTERRUPTS];
IdtGate idt_gates[NUM_OF_INTERRUPTS];
IdtLocation idt_location;

static void init_idt();
static void init_pics();
static void remap_pics();
static void init_irq_gates();
static void set_idt_gate(u8_t idx, u32_t isr_addr, u16_t sel, u8_t flags);

static void send_reset_signal_to_slave();
static void send_reset_signal_to_master();

static int is_valid_int_number(u8_t int_number);

void init_intr(){
	init_idt();
	init_pics();
	load_idt((u32_t)&idt_location);
}

void register_interrupt_handler(u8_t int_number, int_handler_t handler){
	if(is_valid_int_number(int_number)){
		if(interrupt_handlers[int_number] == handler)
			return;
		interrupt_handlers[int_number] = handler;
	}
}

void isr_handler(registers_t regs){
	putsk("Received interrupt: ");
	puthk(regs.int_number);
	putsk("\n");
}

void irq_handler(registers_t registers){

	int_handler_t handler = interrupt_handlers[registers.int_number];
	handler(registers);
	if(registers.int_number >= 40){
		send_reset_signal_to_slave();
	}
	send_reset_signal_to_master();
}

static void init_idt(){

	idt_location.limit = sizeof(idt_gates);
	idt_location.base_addr = (u32_t)idt_gates;
	
	memset(&idt_gates, 0, sizeof(idt_gates));
	set_idt_gate(0, (u32_t)isr_0, KERNEL_CODE, 0x8e);
	set_idt_gate(1, (u32_t)isr_1, KERNEL_CODE, 0x8e);
	set_idt_gate(2, (u32_t)isr_2, KERNEL_CODE, 0x8e);
	set_idt_gate(3, (u32_t)isr_3, KERNEL_CODE, 0x8e);
	set_idt_gate(4, (u32_t)isr_4, KERNEL_CODE, 0x8e);
	set_idt_gate(5, (u32_t)isr_5, KERNEL_CODE, 0x8e);
	set_idt_gate(6, (u32_t)isr_6, KERNEL_CODE, 0x8e);
	set_idt_gate(7, (u32_t)isr_7, KERNEL_CODE, 0x8e);
	set_idt_gate(8, (u32_t)isr_8, KERNEL_CODE, 0x8e);
	set_idt_gate(9, (u32_t)isr_9, KERNEL_CODE, 0x8e);
	set_idt_gate(10, (u32_t)isr_10, KERNEL_CODE, 0x8e);
	set_idt_gate(11, (u32_t)isr_11, KERNEL_CODE, 0x8e);
	set_idt_gate(12, (u32_t)isr_12, KERNEL_CODE, 0x8e);
	set_idt_gate(13, (u32_t)isr_13, KERNEL_CODE, 0x8e);
	set_idt_gate(14, (u32_t)isr_14, KERNEL_CODE, 0x8e);
	set_idt_gate(15, (u32_t)isr_15, KERNEL_CODE, 0x8e);
	set_idt_gate(16, (u32_t)isr_16, KERNEL_CODE, 0x8e);
	set_idt_gate(17, (u32_t)isr_17, KERNEL_CODE, 0x8e);
	set_idt_gate(18, (u32_t)isr_18, KERNEL_CODE, 0x8e);
	set_idt_gate(19, (u32_t)isr_19, KERNEL_CODE, 0x8e);
	set_idt_gate(20, (u32_t)isr_20, KERNEL_CODE, 0x8e);
	set_idt_gate(21, (u32_t)isr_21, KERNEL_CODE, 0x8e);
	set_idt_gate(22, (u32_t)isr_22, KERNEL_CODE, 0x8e);
	set_idt_gate(23, (u32_t)isr_23, KERNEL_CODE, 0x8e);
	set_idt_gate(24, (u32_t)isr_24, KERNEL_CODE, 0x8e);
	set_idt_gate(25, (u32_t)isr_25, KERNEL_CODE, 0x8e);
	set_idt_gate(26, (u32_t)isr_26, KERNEL_CODE, 0x8e);
	set_idt_gate(27, (u32_t)isr_27, KERNEL_CODE, 0x8e);
	set_idt_gate(28, (u32_t)isr_28, KERNEL_CODE, 0x8e);
	set_idt_gate(29, (u32_t)isr_29, KERNEL_CODE, 0x8e);
	set_idt_gate(30, (u32_t)isr_30, KERNEL_CODE, 0x8e);
	set_idt_gate(31, (u32_t)isr_31, KERNEL_CODE, 0x8e);

}

static void init_pics(){
	remap_pics();
	init_irq_gates();		
}

static void remap_pics(){

	out_byte(PIC_MASTER_CMD, ICW1);
	out_byte(PIC_SLAVE_CMD, ICW1);	

	out_byte(PIC_MASTER_DATA, IRQ0_START);
	out_byte(PIC_SLAVE_DATA, IRQ8_START);

	out_byte(PIC_MASTER_DATA, 0x04);
	out_byte(PIC_SLAVE_DATA, 0x02);

	out_byte(PIC_MASTER_DATA, ICW4);
	out_byte(PIC_SLAVE_DATA, ICW4);

	out_byte(PIC_MASTER_DATA, 0xfd);
	out_byte(PIC_SLAVE_DATA, 0xff);
}

static void init_irq_gates(){
	set_idt_gate(32, (u32_t)irq_0, KERNEL_CODE, 0x8e);
	set_idt_gate(33, (u32_t)irq_1, KERNEL_CODE, 0x8e);
	set_idt_gate(34, (u32_t)irq_2, KERNEL_CODE, 0x8e);
	set_idt_gate(35, (u32_t)irq_3, KERNEL_CODE, 0x8e);
	set_idt_gate(36, (u32_t)irq_4, KERNEL_CODE, 0x8e);
	set_idt_gate(37, (u32_t)irq_5, KERNEL_CODE, 0x8e);
	set_idt_gate(38, (u32_t)irq_6, KERNEL_CODE, 0x8e);
	set_idt_gate(39, (u32_t)irq_7, KERNEL_CODE, 0x8e);
	set_idt_gate(40, (u32_t)irq_8, KERNEL_CODE, 0x8e);
	set_idt_gate(41, (u32_t)irq_9, KERNEL_CODE, 0x8e);
	set_idt_gate(42, (u32_t)irq_10, KERNEL_CODE, 0x8e);
	set_idt_gate(43, (u32_t)irq_11, KERNEL_CODE, 0x8e);
	set_idt_gate(44, (u32_t)irq_12, KERNEL_CODE, 0x8e);
	set_idt_gate(45, (u32_t)irq_13, KERNEL_CODE, 0x8e);
	set_idt_gate(46, (u32_t)irq_14, KERNEL_CODE, 0x8e);
	set_idt_gate(47, (u32_t)irq_15, KERNEL_CODE, 0x8e);
}

static void set_idt_gate(u8_t idx, u32_t isr_addr, u16_t sel, u8_t flags){

	idt_gates[idx].isr_addr_low = isr_addr & 0xffff;
	idt_gates[idx].isr_addr_high = (isr_addr >> 16) & 0xffff;
	idt_gates[idx].selector = sel;
	idt_gates[idx].zero = 0;
	idt_gates[idx].flags = flags /*| 0x60*/ ;
}

static void send_reset_signal_to_slave(){
	out_byte(PIC_SLAVE_CMD, 0x20);
}

static void send_reset_signal_to_master(){
	out_byte(PIC_MASTER_CMD, 0x20);
}

static int is_valid_int_number(u8_t int_number){
	int is_valid = 1;
	if(int_number < 0 || int_number >=  NUM_OF_INTERRUPTS)
		is_valid = 0;

	return is_valid;
}

