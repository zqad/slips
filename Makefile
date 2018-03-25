GCC_CPU=attiny85
ISP_CPU=t85
SCK=10
TARGET=slips.hex
SRC_FILES=src/main.c src/melodies.c

# ==================

#AVRDUDE_PORT=/dev/ttyUSB0
#AVRDUDE_ISP=avrispmkII
#AVRDUDE_SUDO=sudo
AVRDUDE_PORT=usb
AVRDUDE_ISP=usbasp #-clone ?

# ==================

CC=avr-gcc
CFLAGS=-mmcu=$(GCC_CPU) -Os -Wall -DF_CPU=1000000L
OBJCOPY=avr-objcopy
OBJARGS=-j .text -j .data -O ihex
AVRDUDE=$(AVRDUDE_SUDO) avrdude -p $(ISP_CPU) -P $(AVRDUDE_PORT) -c $(AVRDUDE_ISP)

# ==================

GENERATED_ASM=$(subst .c,.s,$(SRC_FILES))

.PHONY: sck load read_fuses fuses asm

$(TARGET): $(subst .c,.o,$(SRC_FILES))

asm: $(GENERATED_ASM)

.c.o:

.c.s:
	$(CC) $(CFLAGS) $< -S -o $@

%.hex:
	$(CC) $(CFLAGS) -o $@.o $^
	$(OBJCOPY) $(OBJARGS) $@.o $@

sck:
	( echo sck $(SCK); echo quit ) | $(AVRDUDE) -tuF

load: $(TARGET)
	$(AVRDUDE) -Uflash:w:$(TARGET)

fuses:
	$(AVRDUDE) \
		-U efuse:w:0xFF:m \
		-U hfuse:w:0xDF:m \
		-U lfuse:w:0x62:m

read_fuses:
	$(AVRDUDE) \
		-U efuse:r:m \
		-U hfuse:r:m \
		-U lfuse:r:m

clean:
	rm -f *.o *.hex src/*.o $(GENERATED_ASM) Makefile.depend

# Magic to build Makefile.depend if it does not exist
ifndef DEPEND_RECURSE
ifeq ($(shell test -e Makefile.depend && echo yes),yes)
include Makefile.depend
else
# Do not want to try to do this again when we get called from here, hence the
# recurse block
$(info $(shell make depend DEPEND_RECURSE=1))
include Makefile.depend
endif
endif

depend: Makefile.depend

Makefile.depend: $(SRC_FILES)
	$(CC) $(CFLAGS) -MM $^ > $@
