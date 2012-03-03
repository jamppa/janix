/*
 *      Jani Arvonen 2012
 * */

#include "kernel.h"

void panic(const char* message) {
    putsk("\nKernel panic: ");
    putsk(message);
    putsk("\n");
    for(;;);
}


