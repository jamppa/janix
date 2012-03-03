#ifndef _KERNEL_H_
#define _KERNEL_H_

/*
   * kernel.h - this is the master header which includes other headers. 
   *            contains also prototypes for general purpose functions etc.
   * Jani Arvonen 2012
   *
 */

#define KERNEL_CODE		0x08
#define KERNEL_DATA		0x10

#include <sys/types.h>
#include <string.h>
#include <janix/console.h>
#include <janix/mm.h>
#include "ports.h"
#include "intr.h"
#include "keyboard.h"
#include "clock.h"

extern void panic(const char* message);

#endif
