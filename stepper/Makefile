all:
	avr-gcc -g -Os -mcall-prologues -mmcu=atmega8 -std=c99 -c stepper.c
	avr-gcc -g -Os -mcall-prologues -mmcu=atmega8 -o stepper.elf stepper.o

	avr-objcopy -j .text -j .data -O ihex stepper.elf stepper.hex

install:
	avrdude -p m8 -P usb -c dragon_isp -e -U flash:w:stepper.hex

clean:
	rm -Rf stepper.hex stepper.o stepper.elf
