CC		= gcc
CFLAGS	= -c -Wall -nostdinc -fno-builtin -m32 -I../include

OBJS	= string.o bitmap.o liballoc.o

.c.o:
	$(CC) $(CFLAGS) -o $*.o $<

lib.a: $(OBJS)
	ar rcs lib.a $(OBJS)

clean:
	rm -rf *.o *.a

