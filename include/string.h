#ifndef _STRING_H_
#define _STRING_H_

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned int size_t;
#endif

extern void* memset(void* dest, int val, size_t count);
extern size_t strlen(const char* str);

#endif
