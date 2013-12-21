#ifndef _INTR_H_
#define _INTR_H_

#define NUM_OF_INTERRUPTS		256
#define PIC_MASTER				0x20		/* IO base address for master 8259 */
#define PIC_SLAVE				0xA0		/* IO base address for slave 8259 */
#define PIC_MASTER_CMD			PIC_MASTER
#define PIC_SLAVE_CMD			PIC_SLAVE
#define PIC_MASTER_DATA			(PIC_MASTER + 1)
#define PIC_SLAVE_DATA			(PIC_SLAVE + 1)
#define PIC_EOI					0x20

#define	ICW1					0x11
#define IRQ0_START				0x20
#define IRQ8_START				0x28
#define ICW4					0x01

#define	IRQ0					32
#define IRQ1					33
#define IRQ2					34
#define IRQ3					35
#define IRQ4					36
#define IRQ5					37
#define IRQ6					38
#define IRQ7					39
#define IRQ8					40
#define IRQ9					41
#define IRQ10					42
#define	IRQ11					43
#define IRQ12					44
#define IRQ13					45
#define IRQ14					46
#define IRQ15					47

struct idt_gate {

	u16_t isr_addr_low;
	u16_t selector;
	u8_t zero;
	u8_t flags;
	u16_t isr_addr_high;

} __attribute__ ((packed));
typedef struct idt_gate idt_gate_t; 


struct idt_location {

	u16_t limit;
	u32_t base_addr;

} __attribute__ ((packed));
typedef struct idt_location idt_location_t;

typedef struct registers {

	u32_t ds;
	u32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
	u32_t int_number, error_code;
	u32_t eip, cs, eflags, useresp, ss;

} registers_t;

typedef void (*int_handler_t) (registers_t registers);

extern void register_interrupt_handler(u8_t int_number, int_handler_t handler);
extern void init_intr(void);
extern void isr_handler(registers_t registers);
extern void irq_handler(registers_t registers);
extern void load_idt(u32_t idt_addr);

    // Interrupt Service Routines - CPU dedicated. Actual impls in "isr.s" 

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
