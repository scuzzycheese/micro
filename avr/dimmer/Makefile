all:
	avr-gcc -g -Os -mmcu=atmega8 -c dimmer.c

	avr-gcc -g -Os -mmcu=atmega8 -o dimmer.elf dimmer.o
	avr-objcopy -j .text -j .data -O ihex dimmer.elf dimmer.hex
	avrdude -p m8 -c stk200 -e -U flash:w:dimmer.hex
