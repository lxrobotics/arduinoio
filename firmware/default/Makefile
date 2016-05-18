###############################################################################
# Makefile for the project ArduinoEA
###############################################################################

## General Flags
PROJECT = ArduinoEA
MCU = atmega328p
TARGET = ArduinoEA.elf
CC = avr-gcc

CPP = avr-g++

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99                       -DF_CPU=16000000UL -O0 -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=ArduinoEA.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Objects that must be built in order to link
OBJECTS = main.o gpio.o uart.o analog.o parser.o temperature.o id.o i2c.o servo.o counter.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) ArduinoEA.hex ArduinoEA.eep ArduinoEA.lss size

## Compile
main.o: ../main.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

gpio.o: ../gpio.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

uart.o: ../uart.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

analog.o: ../analog.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

parser.o: ../parser.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

temperature.o: ../temperature.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

id.o: ../id.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

i2c.o: ../i2c.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

servo.o: ../servo.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

counter.o: ../counter.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) ArduinoEA.elf dep/* ArduinoEA.hex ArduinoEA.eep ArduinoEA.lss ArduinoEA.map


## Other dependencies
-include $(shell mkdir dep 2>NUL) $(wildcard dep/*)

