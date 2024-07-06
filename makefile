#!/usr/bin/make -f
# process from here https://www.hackster.io/milanistef/introduction-to-bare-metal-programming-in-arduino-uno-f3e2b4
# modified to use make
# obscuresc June 2024

SRC_DIR = ./src
BLD_DIR = ./build

LOCAL_CC = g++
LOCAL_CI = ./src/
LOCAL_CFLAGS = -D_x86
LOCAL_LDFLAGS = -lspdlog -lfmt 
LOCAL_BLD_DIR = $(BLD_DIR)/local

DEV_CC = avr-gcc
DEV_CFLAGS = -Os -DF_CPU=16000000UL -mmcu=atmega328p -Wall
DEV_BLD_DIR = $(BLD_DIR)/device

DEV_SOURCES = blinky.c clock.c spdlog_interface.c usart.c
DEV_OBJS = $(patsubst %.c, %.o, $(DEV_SOURCES))
# the device and local builds need different compilers
# and I can't just link the objects from one compiler to another
# so, in order to build it properly, i need rules that
# set the compiler for each build AND the target for the object
# either needs to handle both compilers or I make two targets
# one for each compiler

###############################################################################
device: device_init __device
.PHONY: device

device_init: 
	$(eval BLD_DIR=$(DEV_BLD_DIR))
	@mkdir -p $(BLD_DIR)
	$(eval COMPILER=$(DEV_CC))
	$(eval FLAGS=$(DEV_CFLAGS))
.PHONY: device_init

__device: $(DEV_OBJS) 
	$(COMPILER) $(FLAGS) \
		$(addprefix $(BLD_DIR)/, $^) \
		-o $(BLD_DIR)/blinky
	avr-objcopy -O ihex -R .eeprom $(BLD_DIR)/blinky blinky.hex

%.o: 
	$(COMPILER) -c $(FLAGS) $(addprefix $(SRC_DIR)/, $(patsubst %.o, %.c, $@)) -o $(BLD_DIR)/$@

ifeq (0, 1)
clock.o:
	$(COMPILER) -c $(FLAGS) $(SRC_DIR)/clock.c -o $(BLD_DIR)/clock.o

blinky.o:
	$(COMPILER) -c $(FLAGS) $(SRC_DIR)/blinky.c -o $(BLD_DIR)/blinky.o

spdlog_interface.o:
	$(COMPILER) -c $(FLAGS) $(SRC_DIR)/spdlog_interface.c -o $(BLD_DIR)/spdlog_interface.o

usart.o:
	$(COMPILER) -c $(FLAGS) $(SRC_DIR)/usart.c -o $(BLD_DIR)/usart.o

flash: device
	avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:blinky.hex
.PHONY: flash
endif

###############################################################################
local: local_init __local
.PHONY: local

local_init:
	$(eval BLD_DIR=$(LOCAL_BLD_DIR))
	@mkdir -p $(BLD_DIR)
	$(eval COMPILER=$(LOCAL_CC))
	$(eval FLAGS=$(LOCAL_CFLAGS))
	$(eval FLAGS+=$(LOCAL_LDFLAGS))
.PHONY: local_init 

__local: local_init blinky.o delay usart.o
	$(COMPILER) $(FLAGS) -I $(LOCAL_CI) \
		$(BLD_DIR)/blinky.o \
		$(BLD_DIR)/delay.o \
		$(BLD_DIR)/usart.o \
		-o $(BLD_DIR)/blinky

delay:
	$(COMPILER) -c $(FLAGS) $(LOCAL_LDFLAGS) $(SRC_DIR)/x86/delay.cpp -o $(BLD_DIR)/delay.o


###############################################################################
clean:
	rm -rf ./build blinky.hex
.PHONY: clean

