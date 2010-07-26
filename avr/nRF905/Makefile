all:
	avr-gcc -g -Os -mcall-prologues -mmcu=atmega8 -std=c99 -c nrf905.c
	avr-gcc -g -Os -mcall-prologues -mmcu=atmega8 -o nrf905.elf nrf905.o

	avr-objcopy -j .text -j .data -O ihex nrf905.elf nrf905.hex

install:
	avrdude -p m8 -P usb -c dragon_isp -e -U flash:w:nrf905.hex

clean:
	rm -Rf nrf905.hex nrf905.o nrf905.elf
