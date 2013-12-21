# Main Makefile for janix

MAKE		= exec make
PARTS		= boot/boot.bin lib/lib.a kernel/kernel.bin

all:		kernelimage

kernelimage: $(PARTS) image

image:
	cp -v kernel/kernel.elf iso/boot/ && \
	genisoimage -R -b boot/grub/stage2_eltorito \
	-no-emul-boot -boot-load-size 4 -A os \
	-input-charset utf8 -quiet -boot-info-table -o janix.iso iso

boot/boot.bin:
	(cd boot; make)

lib/lib.a:
	(cd lib; make)

kernel/kernel.bin: lib/lib.a
	(cd kernel; make)

clean:
	(rm -f janix.iso bochslog.txt)

deepclean: clean
	(cd boot; make clean) 
	(cd kernel; make clean)
	(cd lib; make clean)

run-bochs:
	bochs -f bochs.txt -q
