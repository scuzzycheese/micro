all: test-avr

test-x86: test.c coroData.h
	gcc -g3 -O0 -o test test.c

test-avr: test.c coroData.h
	avr-gcc -g -O0 -mcall-prologues -mmcu=atmega48 -std=c99 -c test.c
	avr-gcc -g -O0 -mcall-prologues -mmcu=atmega48 -o test.elf test.o

	avr-objcopy -j text -j .data -O ihex test.elf test.hex

install:
	avrdude -p m8 -P usb -c dragon_isp -e -U flash:w:test.hex

clean:
	rm -rf test
