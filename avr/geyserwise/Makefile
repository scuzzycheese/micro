all:
	avr-gcc -g -Os -mmcu=atmega8 -c geyserwise.c -I.

	avr-gcc -g -Os -mmcu=atmega8 -o geyserwise.elf geyserwise.o
	avr-objcopy -j .text -j .data -O ihex geyserwise.elf geyserwise.hex

install:
	avrdude -p m8 -c dragon_isp -P usb -U flash:w:geyserwise.hex
