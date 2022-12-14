EE_ELF = code.elf
EE_BIN = code.bin
EE_S = code.s
EE_OBJS = main.o
EE_LIBS = -ldl -lkernel

EE_INCS := -I../../include -I$(PS2SDK)/ports/include
EE_LDFLAGS = -fno-builtin -nostdlib -nostartfiles -L. -L../../lib -L$(PS2SDK)/ports/lib
EE_LDFLAGS += -s
#EE_DEFS = -DDEBUG

all: the_copy_bin make_s the_copy_s

# make copy.bin and copy it to bin/
the_copy_bin: $(EE_BIN) copy

# Convert code.bin to code.S
make_s:
	bin2s $(EE_ELF) $(EE_S) Chaos_Codes

# copy code.S to /../Kernel/ and then clean_some
the_copy_s: $(EE_S) copy_s clean_some

clean:
	rm -f *.irx *.o *.bin *.elf code.s

clean_some:
	rm -f *.irx *.o code.s

include $(CURDIR)/../Makefile.pref
include $(CURDIR)/../Makefile.eeglobal
include ${CURDIR}/../Makefile.rules
