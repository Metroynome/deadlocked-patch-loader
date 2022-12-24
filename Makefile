all:
	$(MAKE) -C Codes
	$(MAKE) -C Kernel
	cat $(CURDIR)/template/patch-template.bin > $(CURDIR)/bin/patch.bin
	dd conv=notrunc bs=1 if=$(CURDIR)/Kernel/kernel.bin of=patch.bin seek=256	
#	$(MAKE) -C bin

clean:
	$(MAKE) -C Codes clean
	$(MAKE) -C Kernel clean
	$(MAKE) -C bin clean