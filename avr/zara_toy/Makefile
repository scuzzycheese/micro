all:
	avr-gcc -g -Os -mcall-prologues -mmcu=atmega8 -c zara_toy.c

	avr-gcc -g -Os -mcall-prologues -mmcu=atmega8 -o zara_toy.elf zara_toy.o
	avr-objcopy -j .text -j .data -O ihex zara_toy.elf zara_toy.hex
install:
	avrdude -p m8 -P usb -c dragon_isp -e -U flash:w:zara_toy.hex
