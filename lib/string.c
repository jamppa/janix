/*
   *	string.c - functions related to string/memory manipulation
   *
   *	Jani Arvonen 2010
 */

#include <sys/types.h>
#include <string.h>

void* memset(void* dest, int c, size_t n){

	size_t i;
	char* p_dest = (char *)dest;
	for(i = 0; i < n; i++){
		*p_dest++ = c;
	}
	return dest;
}
