NAME = atmega328p
F_CPU = 16000000UL

SRC = main.c
BIN = main.bin
HEX = main.hex

CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

hex :
	$(CC) -mmcu=$(NAME) -DF_CPU=$(F_CPU) -Os -I/usr/lib/avr/include -o $(BIN) $(SRC)
	$(OBJCOPY) -O ihex $(BIN) $(HEX)

flash :
	avrdude -c arduino -p $(NAME) -b 115200 -P /dev/ttyUSB0 -U flash:w:$(HEX)

all : hex flash

clean :
	rm -f $(BIN) $(HEX)
