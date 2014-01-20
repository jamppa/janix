#ifndef _KERNEL_H_
#define _KERNEL_H_

#define KERNEL_CODE		0x08
#define KERNEL_DATA		0x10

#include <sys/types.h>
#include <string.h>
#include <bitmap.h>
#include <janix/console.h>
#include <janix/mm.h>
#include "gdt.h"
#include "ports.h"
#include "intr.h"
#include "keyboard.h"
#include "clock.h"
#include "traps.h"

extern void panic(const char* message);

#endif
