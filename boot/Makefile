# Makefile for boot.asm and kernel.asm
#
# Jani Arvonen - 2010

AS      = nasm
AFLAGS  := -f bin

all:    boot.bin 

boot.bin:
		$(AS) $(AFLAGS) boot.asm -o boot.bin

clean:
		rm -rf *.bin
