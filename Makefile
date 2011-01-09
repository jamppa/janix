# Main Makefile for janix

MAKE		= exec make
PARTS		= boot/boot.bin lib/lib.a kernel/kernel.bin

all:		kernelimage

kernelimage: $(PARTS) image

image:
	cp boot/boot.bin . && cp kernel/kernel.bin . && cat boot.bin kernel.bin > kernel.img

boot/boot.bin:
	cd boot && make

lib/lib.a:
	cd lib && make

kernel/kernel.bin:
	cd kernel && make

clean:
	rm -f boot.bin kernel.bin kernel.img;

deepclean: clean
	cd boot; make clean; cd ..; cd kernel; make clean; cd ..; cd lib; make clean; cd ..;
