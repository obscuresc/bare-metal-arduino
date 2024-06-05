#!/usr/bin/make -f
# process from here https://www.hackster.io/milanistef/introduction-to-bare-metal-programming-in-arduino-uno-f3e2b4
# modified to use make
# obscuresc June 2024

SRC_DIR = ./src
BLD_DIR = ./build

LOCAL_CC = g++
LOCAL_CI = ./src/

DEV_CC = avr-gcc
DEV_CFLAGS = -Os -DF_CPU=16000000UL

# avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o blinky.o blinky.c
# avr-gcc -mmcu=atmega328p blinky.o -o blinky
# avr-objcopy -O ihex -R .eeprom blinky blinky.hex
# avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:blinky.hex

device:
	@mkdir -p $(BLD_DIR)/$@
	$(DEV_CC) $(DEV_CFLAGS) -mmcu=atmega328p -c -o $(BLD_DIR)/$@/blinky.o $(SRC_DIR)/blinky.c
	$(DEV_CC) -mmcu=atmega328p $(BLD_DIR)/$@/blinky.o -o $(BLD_DIR)/$@/blinky
	avr-objcopy -O ihex -R .eeprom $(BLD_DIR)/$@/blinky blinky.hex

flash: device
	avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:blinky.hex

local:
	@mkdir -p $(BLD_DIR)/$@
	$(LOCAL_CC) -D _x86 -I $(LOCAL_CI) $(SRC_DIR)/blinky.c -o $(BLD_DIR)/$@/blinky

clean:
	rm -rf ./build blinky.hex

.PHONY:
	clean
