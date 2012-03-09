#ifndef _TRAPS_H_
#define _TRAPS_H_

#include "intr.h"

#define DIVISION_OVERFLOW_GATE          0x00
#define SINGLE_STEP_GATE                0x01
#define NMI_GATE                        0x02
#define BREAKPOINT_GATE                 0x03
#define OVERFLOW_GATE                   0x04
#define BOUND_RANGE_GATE                0x05
#define INVALID_OP_GATE                 0x06
#define NOT_AVAILABLE_GATE              0x07
#define DOUBLE_FAULT_GATE               0x08
#define SEGMENT_OVERRUN_GATE            0x09
#define INVALID_TSS_GATE                0x0a
#define SEGMENT_NOT_PRESENT_GATE        0x0b
#define STACK_OVERFLOW_GATE             0x0c
#define GENERAL_PROTECTION_FAULT_GATE   0x0d
#define RESERVED_GATE                   0x0f
#define ERROR_GATE                      0x10

extern void init_traps(void);
extern void die(const char* msg, registers_t* registers);

#endif
