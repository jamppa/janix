# Main Makefile for janix

MAKE		= exec make
PARTS		= boot/boot.bin lib/lib.a kernel/kernel.bin

all:		kernelimage

kernelimage: $(PARTS) image

image:
	cat boot/boot.bin kernel/kernel.bin > kernel.img

boot/boot.bin:
	(cd boot; make)

lib/lib.a:
	(cd lib; make)

kernel/kernel.bin: lib/lib.a
	(cd kernel; make)

clean:
	(rm -f boot.bin kernel.bin kernel.img)

deepclean: clean
	(cd boot; make clean) 
	(cd kernel; make clean)
	(cd lib; make clean)
