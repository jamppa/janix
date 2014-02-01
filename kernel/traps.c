#include "kernel.h"

static void division_overflow(registers_t regs);
static void single_step(registers_t regs);
static void nmi(registers_t regs);
static void breakpoint(registers_t regs);
static void overflow(registers_t regs);
static void bound_range(registers_t regs);
static void invalid_op(registers_t regs);
static void not_available(registers_t regs); 
static void double_fault(registers_t regs);
static void segment_overrun(registers_t regs);
static void invalid_tss(registers_t regs);
static void segment_not_present(registers_t regs);
static void stack_overflow(registers_t regs);
static void general_protection_fault(registers_t regs);
static void error(registers_t regs);
static void reserved(registers_t regs);

void init_traps(void) {
    
    register_interrupt_handler(DIVISION_OVERFLOW_GATE, &division_overflow);
    register_interrupt_handler(SINGLE_STEP_GATE, &single_step);
    register_interrupt_handler(NMI_GATE, &nmi);
    register_interrupt_handler(BREAKPOINT_GATE, &breakpoint);
    register_interrupt_handler(OVERFLOW_GATE, &overflow);
    register_interrupt_handler(BOUND_RANGE_GATE, &bound_range);
    register_interrupt_handler(INVALID_OP_GATE, &invalid_op);
    register_interrupt_handler(NOT_AVAILABLE_GATE, &not_available);
    register_interrupt_handler(DOUBLE_FAULT_GATE, &double_fault);
    register_interrupt_handler(SEGMENT_OVERRUN_GATE, &segment_overrun);
    register_interrupt_handler(INVALID_TSS_GATE, &invalid_tss);
    register_interrupt_handler(SEGMENT_NOT_PRESENT_GATE, &segment_not_present);
    register_interrupt_handler(STACK_OVERFLOW_GATE, &stack_overflow);
    register_interrupt_handler(GENERAL_PROTECTION_FAULT_GATE, &general_protection_fault);
    register_interrupt_handler(ERROR_GATE, &error);
    register_interrupt_handler(RESERVED_GATE, &reserved);

    int i = RESERVED_GATE + 2;
    for(; i < 32; i++){
        register_interrupt_handler(i, &reserved);
    }

}

static void print_eip(registers_t* registers){
    printk("EIP:\t%04x:%p", registers->cs, registers->eip); 
}

static void print_eflags(registers_t* registers) {
    printk("\nEFLAGS:\t%p", registers->eflags);
}

static void print_registers(registers_t* registers) {
    printk("\n\neax: %08x\tebx: %08x\tecx: %08x\tedx: %08x", registers->eax, registers->ebx, registers->ecx, registers->edx);   
    printk("\nesi: %08x\tedi: %08x\tebp: %08x\tesp: %08x", registers->esi, registers->edi, registers->ebp, registers->esp);
}

static void print_segments(registers_t* registers) {
    printk("\nds: %08x\tss: %08x", registers->ds, registers->ss);
}

void die(const char* msg, registers_t* registers) {
    printk("\n%s\n", msg);
    print_eip(registers);
    print_eflags(registers);
    print_registers(registers);
    print_segments(registers);
}

static void division_overflow(registers_t regs) {
    die("division overflow:", &regs);
}

static void single_step(registers_t regs) {
    die("single step:", &regs);
}

static void nmi(registers_t regs) {
    die("nmi:", &regs);
}

static void breakpoint(registers_t regs){
    die("breakpoint:", &regs);
}

static void overflow(registers_t regs){
    die("overflow:", &regs);
}

static void bound_range(registers_t regs){
    die("bound range:", &regs);
}

static void invalid_op(registers_t regs) {
    die("invalid machine code:", &regs);
}

static void not_available(registers_t regs) {
    die("device not available:", &regs);
}

static void double_fault(registers_t regs) {
    die("double fault:", &regs);
}

static void segment_overrun(registers_t regs){
    die("segment overrun:", &regs);
}

static void invalid_tss(registers_t regs){
    die("invalid task state segment:", &regs);
}

static void segment_not_present(registers_t regs){
    die("segment not present:", &regs);
}

static void stack_overflow(registers_t regs){
    die("stack overflow:", &regs);
}

static void general_protection_fault(registers_t regs){
    die("general protection fault:", &regs);
}

static void error(registers_t regs){
    die("error:", &regs);
}

static void reserved(registers_t regs){
    die("reserved (15, 17-31) error:", &regs);
}

