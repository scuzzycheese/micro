all:
	avr-gcc -g -Os -mmcu=atmega8 -c test.c

	avr-gcc -g -Os -mmcu=atmega8 -o test.elf test.o
	avr-objcopy -j .text -j .data -O ihex test.elf test.hex
	avrdude -p m8 -c stk200 -e -U flash:w:test.hex
