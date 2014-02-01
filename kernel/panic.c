#include "kernel.h"

void panic(const char* message) {
    printk("\nKernel panic - %s", message);
    for(;;);
}


