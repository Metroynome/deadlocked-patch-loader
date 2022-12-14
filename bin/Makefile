all:
	cat $(CURDIR)/../template/patch-template.bin > $(CURDIR)/patch.bin
	dd conv=notrunc bs=1 if=$(CURDIR)/kernel.bin of=patch.bin seek=256
	dd conv=notrunc bs=1 if=$(CURDIR)/code.bin of=patch.bin seek=4096
	
clean:
	rm -f *.irx *.o *.bin *.elf *.S

include $(CURDIR)/../Makefile.pref
include $(CURDIR)/../Makefile.eeglobal
include $(CURDIR)/../Makefile.rules