EE_ELF = kernel.elf
EE_BIN = kernel.bin
EE_OBJS = main.o
EE_LIBS = -ldl -lkernel

EE_INCS := -I../../include -I$(PS2SDK)/ports/include
EE_LDFLAGS = -fno-builtin -nostdlib -nostartfiles -L. -L../libdl/lib
#EE_DEFS = -DDEBUG

all: $(EE_BIN) clean copy

clean:
	rm -f *.irx *.o *.bin *.elf

include $(CURDIR)/../Makefile.pref
include $(CURDIR)/../Makefile.eeglobal
include ${CURDIR}/../Makefile.rules

