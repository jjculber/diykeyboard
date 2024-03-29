###############################################################################
# Makefile for the project AVR-MIDI
###############################################################################

# If using the tools from macports on a mac, you'll need to do something like:
# sudo port install avr-gcc avr-libc avrdude

# If using the tools that come with Arduino on a mac, make sure you have something like this on your path:
# /Applications/arduino-0014/hardware/tools/avr/bin/

## General Flags
PROJECT = midimega
MCU = atmega168
TARGET = $(PROJECT).elf
DEBUG =  -DDEBUG_LEVEL=2
CC = avr-gcc
AVRDUDE = avrdude -C /Applications/arduino-0014/hardware/tools/avr/etc/avrdude.conf -c usbtiny -p$(MCU)

# mcu clock freq, in Hz.
FREQUENCY = 16000000

FUSEH = 0xc1
FUSEL = 0x9f
# Fuse high byte:
# 0xc0 = 1 1 0 0   0 0 0 1 <-- BOOTRST (boot reset vector at 0x3800)
#        ^ ^ ^ ^   ^ ^ ^------ BOOTSZ0
#        | | | |   | +-------- BOOTSZ1
#        | | | |   + --------- EESAVE (preserve EEPROM over chip erase)
#        | | | +-------------- CKOPT (full output swing)
#        | | +---------------- SPIEN (allow serial programming)
#        | +------------------ WDTON (WDT not always on)
#        +-------------------- RSTDISBL (reset pin is enabled)
# Fuse low byte:
# 0x9f = 1 0 0 1   1 1 1 1
#        ^ ^ \ /   \--+--/
#        | |  |       +------- CKSEL 3..0 (external >8M crystal)
#        | |  +--------------- SUT 1..0 (crystal osc, BOD enabled)
#        | +------------------ BODEN (BrownOut Detector enabled)
#        +-------------------- BODLEVEL (2.7V)


## Options common to compile, link and assembly rules
COMMON = -g -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -DF_CPU=${FREQUENCY}UL -Os -fsigned-char  $(DEBUG)

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += -x assembler-with-cpp -Wa,

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=$(PROJECT).map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom


## Include Directories
INCLUDES = -I"." -I"../usbdrv" -I"../." 

## Objects that must be built in order to link
OBJECTS = usbdrv.o usbdrvasm.o oddebug.o main.o

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) $(PROJECT).hex $(PROJECT).lss size

$(OBJECTS): usbconfig.h Makefile

## Compile
usbdrv.o: ../usbdrv/usbdrv.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usbdrvasm.o: ../usbdrv/usbdrvasm.S
	$(CC) $(INCLUDES) $(ASMFLAGS) -c  $<

oddebug.o: ../usbdrv/oddebug.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

main.o: main.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@./checksize ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) $(PROJECT).* *~


.PHONY: flash
flash:	all
	$(AVRDUDE) -U flash:w:$(PROJECT).hex


.PHONY: fuse
fuse:
	$(AVRDUDE) -U hfuse:w:$(FUSEH):m -U lfuse:w:$(FUSEL):m

