all:
	avr-gcc -g -Os -mcall-prologues -mmcu=atmega8 -std=c99 -c tiny13.c
	avr-gcc -g -Os -mcall-prologues -mmcu=atmega8 -o tiny13.elf tiny13.o

	avr-objcopy -j .text -j .data -O ihex tiny13.elf tiny13.hex

install:
	avrdude -p t13 -P usb -c dragon_isp -e -U flash:w:tiny13.hex

clean:
	rm -Rf tiny13.hex tiny13.o tiny13.elf
