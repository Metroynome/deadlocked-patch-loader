all:
	$(MAKE) -C Kernel
	$(MAKE) -C Codes
	$(MAKE) -C bin

clean:
	$(MAKE) -C Kernel clean
	$(MAKE) -C Codes clean
	$(MAKE) -C bin clean