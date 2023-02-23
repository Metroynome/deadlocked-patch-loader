KERNEL_BIN = $(CURDIR)/kernel.bin
PATCH_TEMPLATE = $(CURDIR)/../template/patch-template.bin

all: check_size make_patch.bin

check_size:
#	Test to see if kernel.bin is too big.
#	if file size is greater than 65270 bytes, don't write to patch.bin.
	test -n "$$(find $(KERNEL_BIN) -a -size -65270c)"

make_patch.bin:
	cat $(PATCH_TEMPLATE) > $(CURDIR)/patch.bin
	dd conv=notrunc bs=1 if=$(KERNEL_BIN) of=patch.bin seek=256

clean:
	rm -f *.irx *.o *.bin *.elf *.S

include $(CURDIR)/../Makefile.pref
include $(CURDIR)/../Makefile.eeglobal
include $(CURDIR)/../Makefile.rules