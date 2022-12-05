EE_ELF = code.elf
EE_BIN = code.bin
EE_OBJS = main.o
EE_LIBS = -ldl -lkernel

EE_INCS := -I../../include -I$(PS2SDK)/ports/include
EE_LDFLAGS = -fno-builtin -nostdlib -nostartfiles -L. -L../../lib -L$(PS2SDK)/ports/lib
#EE_DEFS = -DDEBUG

all: $(EE_BIN) clean copy

clean:
	rm -f *.irx *.o

include $(CURDIR)/../Makefile.pref
include $(CURDIR)/../Makefile.eeglobal
include ${CURDIR}/../Makefile.rules
