EE_ELF = kernel.elf
EE_BIN = kernel.bin
EE_OBJS = main.o
EE_LIBS = -ldl -lkernel

EE_INCS := -I../../include -I$(PS2SDK)/ports/include
EE_LDFLAGS = -fno-builtin -nostdlib -nostartfiles -L. -L../libdl/lib
#EE_DEFS = -DDEBUG

all: $(EE_BIN) copy clean_some

clean:
	rm -f *.irx *.o *.bin *.elf code.S

clean_some:
	rm -f *.irx *.o

include $(CURDIR)/../Makefile.pref
include $(CURDIR)/../Makefile.eeglobal
include ${CURDIR}/../Makefile.rules

