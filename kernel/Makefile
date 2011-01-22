# Makefile for kernel
#
# Jani Arvonen 2010

CC			= gcc
CFLAGS		:= -c -Wall -fno-builtin -fomit-frame-pointer -nostdinc -nostdlib -I../include
AS			= nasm
AFLAGS		:= -f aout
LS			= link.ld
LIBS		= ../lib/lib.a

.c.o:   
		$(CC) $(CFLAGS) -o $*.o $<
.s.o:
		$(AS) $(AFLAGS) -o $*.o $<

OBJS		= kstart.o kmain.o ports.o intr.o isr.o console.o \
			  keyboard.o

kernel.o: $(OBJS)
		ld -T $(LS) -o kernel.bin $(OBJS) $(LIBS)

clean:
		rm -rf *.bin *.o
