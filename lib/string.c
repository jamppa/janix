#include <string.h>
#include <sys/types.h>

void* memset(void* dest, int c, size_t n){

	size_t i;
	char* p_dest = (char *)dest;
	for(i = 0; i < n; i++){
		*p_dest++ = c;
	}
	return dest;
}

size_t strlen(const char* str) {
    const char* i = str;
    while(*i++ != '\0') {}
    return i - str - 1;
}