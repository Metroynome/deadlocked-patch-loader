EE_ELF = kernel.elf
EE_BIN = kernel.bin
EE_OBJS = main.o codes.o exceptiondisplay.o
EE_LIBS = -ldlsp -lkernel

EE_INCS := -I../../include -I$(PS2SDK)/ports/include
EE_LDFLAGS = -fno-builtin -nostdlib -nostartfiles -L. -L../libdl/lib
EE_DEFS = -DDEBUG

all: exceptiondisplay.s kernel.bin clean_some copy

# Make Kernel.elf/bin.
kernel.bin: $(EE_BIN)

# Convert exceptiondisplay.bin to exceptiondisplay.s
exceptiondisplay.s:
	bin2s $(CURDIR)/../template/exceptiondisplay.bin exceptiondisplay.s exceptiondisplay

clean:
	rm -f *.irx *.o *.bin *.elf codes.s exceptiondisplay.s

clean_some:
	rm -f *.irx *.o

include $(CURDIR)/../Makefile.pref
include $(CURDIR)/../Makefile.eeglobal
include ${CURDIR}/../Makefile.rules

