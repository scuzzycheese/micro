all:
	avr-gcc -g -Os -mmcu=atmega8 -c switch.c

	avr-gcc -g -Os -mmcu=atmega8 -o switch.elf switch.o
	avr-objcopy -j .text -j .data -O ihex switch.elf switch.hex
	avrdude -p m8 -c stk200 -e -U flash:w:switch.hex
