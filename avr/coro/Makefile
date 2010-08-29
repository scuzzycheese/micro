all: test-avr

test-x86: test.c fibre.h fibre.c
	gcc -g3 -O0 -o test fibre.c test.c

test-avr: test.c fibre.h fibre.c
	avr-gcc -g -O0 -mcall-prologues -mmcu=atmega48 -std=c99 -c fibre.c
	avr-gcc -g -O0 -mcall-prologues -mmcu=atmega48 -std=c99 -c test.c
	avr-gcc -g -O0 -mcall-prologues -mmcu=atmega48 fibre.o test.o -o test.elf

	avr-objcopy -j text -j .data -O ihex test.elf test.hex

install:
	avrdude -p m8 -P usb -c dragon_isp -e -U flash:w:test.hex

clean:
	rm -rf test fibre.o test.o test.elf test.hex
