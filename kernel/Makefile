CC			= gcc
CFLAGS		:= -c -Wall -fno-builtin -fomit-frame-pointer -nostdinc -nostdlib -m32 -I../include
AS			= nasm
AFLAGS		:= -f elf32
LS			= link.ld
LIBS		= ../lib/lib.a

.c.o:   
		$(CC) $(CFLAGS) -o $*.o $<
.s.o:
		$(AS) $(AFLAGS) -o $*.o $<

OBJS		= kstart.o kmain.o gdt.o ports.o intr.o isr.o descriptor_tables.o console.o \
			  keyboard.o tty.o clock.o panic.o traps.o ../mm/kmalloc.o ../mm/page.o ../mm/mmap.o \
			  ../mm/paging.o

kernel.o: $(OBJS)
		ld -T $(LS) -o kernel.elf -melf_i386 $(OBJS) $(LIBS)

clean:
		rm -rf *.elf *.bin *.o; cd ../mm; rm -rf *.o;
