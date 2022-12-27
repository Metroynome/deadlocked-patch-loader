EE_ELF = codes.elf
EE_BIN = codes.bin
EE_S = codes.s
EE_OBJS = main.o
EE_LIBS = -ldl -lkernel

EE_INCS := -I../../include -I$(PS2SDK)/ports/include
EE_LDFLAGS = -fno-builtin -nostdlib -nostartfiles -L. -L../../lib -L$(PS2SDK)/ports/lib
EE_LDFLAGS += -s
#EE_DEFS = -DDEBUG

all: codes.bin codes.s then_copy_s codes.pnach

# make copy.bin, but don't copy to /bin
codes.bin: $(EE_BIN)

# Convert code.bin to codes.s
codes.s:
	bin2s $(EE_ELF) $(EE_S) codes

# copy codes.s to /../Kernel/ and then clean_some
then_copy_s: $(EE_S) copy_s clean_some

clean:
	rm -f *.irx *.o *.bin *.elf codes.s

clean_some:
	rm -f *.irx *.o codes.s

codes.pnach:
	bin2code $(EE_BIN) 000F0000 codes.pnach pnach
	cat $(CURDIR)/../template/codes-footer.pnach >> codes.pnach

include $(CURDIR)/../Makefile.pref
include $(CURDIR)/../Makefile.eeglobal
include ${CURDIR}/../Makefile.rules
