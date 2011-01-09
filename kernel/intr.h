#ifndef _INTR_H_
#define _INTR_H_

#define NUM_OF_INTERRUPTS		256
#define PIC_MASTER				0x20		/* IO base address for master 8259 */
#define PIC_SLAVE				0xA0		/* IO base address for slave 8259 */
#define PIC_MASTER_CMD			PIC_MASTER
#define PIC_SLAVE_CMD			PIC_SLAVE
#define PIC_MASTER_DATA			(PIC_MASTER + 1)
#define PIC_SLAVE_DATA			(PIC_SLAVE + 1)
#define PIC_EOI					0x20		/* end of interrupt command */

#define	ICW1					0x11
#define IRQ0_START				0x20
#define IRQ8_START				0x28
#define ICW4					0x01

/*
   *	Interrupt Descriptor Table Gate Layout
 */
struct idt_gate {

	u16_t isr_addr_low;
	u16_t selector;
	u8_t zero;
	u8_t flags;
	u16_t isr_addr_high;

} __attribute__ ((packed));
typedef struct idt_gate IdtGate; 


/*
   *	structure holding information about location of IDT
 */
struct idt_location {

	u16_t limit;
	u32_t base_addr;

} __attribute__ ((packed));
typedef struct idt_location IdtLocation;

/*
   *	registers structure
 */
typedef struct registers {

	u32_t ds;
	u32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
	u32_t int_number, error_code;
	u32_t eip, cs, eflags, useresp, ss;

} registers_t;

/*
   *	interrupt / IDT related functions
 */
extern void init_intr(void);
extern void isr_handler(registers_t registers);
extern void irq_handler(registers_t registers);
extern void load_idt(u32_t idt_addr);

/*
   *	Interrupt Service Routines - CPU dedicated. Actual impls in "isr.s" 
 */
extern void isr_0();
extern void isr_1();
extern void isr_2();
extern void isr_3();
extern void isr_4();
extern void isr_5();
extern void isr_6();
extern void isr_7();
extern void isr_8();
extern void isr_9();
extern void isr_10();
extern void isr_11();
extern void isr_12();
extern void isr_13();
extern void isr_14();
extern void isr_15();
extern void isr_16();
extern void isr_17();
extern void isr_18();
extern void isr_19();
extern void isr_20();
extern void isr_21();
extern void isr_22();
extern void isr_23();
extern void isr_24();
extern void isr_25();
extern void isr_26();
extern void isr_27();
extern void isr_28();
extern void isr_29();
extern void isr_30();
extern void isr_31();

/*
   *	IRQ service routines
 */
extern void irq_0();
extern void irq_1();
extern void irq_2();
extern void irq_3();
extern void irq_4();
extern void irq_5();
extern void irq_6();
extern void irq_7();
extern void irq_8();
extern void irq_9();
extern void irq_10();
extern void irq_11();
extern void irq_12();
extern void irq_13();
extern void irq_14();
extern void irq_15();

#endif