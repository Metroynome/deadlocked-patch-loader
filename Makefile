all:
	$(MAKE) -C Codes
	$(MAKE) -C Kernel
	$(MAKE) -C bin

clean:
	$(MAKE) -C Codes clean
	$(MAKE) -C Kernel clean
	$(MAKE) -C bin clean