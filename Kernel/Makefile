EE_ELF = kernel.elf
EE_BIN = kernel.bin
EE_OBJS = main.o codes.o
EE_LIBS = -ldl -lkernel

EE_INCS := -I../../include -I$(PS2SDK)/ports/include
EE_LDFLAGS = -fno-builtin -nostdlib -nostartfiles -L. -L../libdl/lib
EE_DEFS = -DDEBUG

# Make Kernel.elf/bin, but do not copy.
all: $(EE_BIN) clean_some copy

clean:
	rm -f *.irx *.o *.bin *.elf codes.s

clean_some:
	rm -f *.irx *.o

include $(CURDIR)/../Makefile.pref
include $(CURDIR)/../Makefile.eeglobal
include ${CURDIR}/../Makefile.rules

