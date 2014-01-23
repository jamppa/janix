#include <stdarg.h>
#include <janix/console.h>

static char buf[1024];

int printk(const char* format, ...) {

    va_list args;
    int printed;

    va_start(args, format);
    printed = vsprintf(buf, format, args);
    va_end(args);

    putsk(buf);
    return printed;
}