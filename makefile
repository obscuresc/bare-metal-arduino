#!/usr/bin/make -f
# process from here https://www.hackster.io/milanistef/introduction-to-bare-metal-programming-in-arduino-uno-f3e2b4
# modified to use make
# obscuresc June 2024

SRC_DIR = ./src
BLD_DIR = ./build

LOCAL_CC = g++
LOCAL_CI = ./src/
LOCAL_LDFLAGS = -lspdlog -lfmt 
LOCAL_BLD_DIR = $(BLD_DIR)/local

DEV_CC = avr-gcc
DEV_CFLAGS = -Os -DF_CPU=16000000UL -mmcu=atmega328p -Wall
DEV_BLD_DIR = $(BLD_DIR)/device


###############################################################################
device: device_init blinky.o clock.o spdlog_interface.o usart.o
	$(DEV_CC) $(DEV_CFLAGS) $(DEV_BLD_DIR)/blinky.o $(DEV_BLD_DIR)/spdlog_interface.o \
		$(DEV_BLD_DIR)/usart.o -o $(DEV_BLD_DIR)/blinky
	avr-objcopy -O ihex -R .eeprom $(DEV_BLD_DIR)/blinky blinky.hex


device_init:
	@mkdir -p $(DEV_BLD_DIR)
.PHONY: device_init

clock.o:
	$(DEV_CC) -c $(DEV_CFLAGS) $(SRC_DIR)/clock.c -o $(DEV_BLD_DIR)/clock.o

blinky.o:
	$(DEV_CC) -c $(DEV_CFLAGS) $(SRC_DIR)/blinky.c -o $(DEV_BLD_DIR)/blinky.o


spdlog_interface.o:
	$(DEV_CC) -c $(DEV_CFLAGS) $(SRC_DIR)/spdlog_interface.c -o $(DEV_BLD_DIR)/spdlog_interface.o

usart.o:
	$(DEV_CC) -c $(DEV_CFLAGS) $(SRC_DIR)/usart.c -o $(DEV_BLD_DIR)/usart.o


flash: device
	avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:blinky.hex
.PHONY: flash


###############################################################################
local: local_init delay usart.o
	$(LOCAL_CC) -D _x86 -I $(LOCAL_CI) $(SRC_DIR)/blinky.c $(LOCAL_LDFLAGS) \
		$(LOCAL_BLD_DIR)/delay.o \
		$(LOCAL_BLD_DIR)/usart.o \
		-o $(LOCAL_BLD_DIR)/blinky


local_init:
	@mkdir -p $(LOCAL_BLD_DIR)
.PHONY: local_init


delay:
	$(LOCAL_CC) -c -D _x86 $(LOCAL_LDFLAGS) $(SRC_DIR)/x86/delay.cpp -o $(LOCAL_BLD_DIR)/delay.o


###############################################################################
clean:
	rm -rf ./build blinky.hex
.PHONY: clean

