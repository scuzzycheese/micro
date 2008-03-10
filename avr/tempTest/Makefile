all:
	avr-gcc -g -Os -mmcu=atmega644 -c test.c -o test.o
	avr-gcc -g -Os -mmcu=atmega644 -c uart.c -o uart.o
	avr-gcc -g -Os -mmcu=atmega644 -o test.elf test.o uart.o

clean:
	rm *.o
	rm *.elf

install-dragon: test.elf
	avr-objcopy -j .text -j .data -O ihex test.elf test.hex
	avrdude -p m644 -c dragon_isp -P usb -e -U flash:w:test.hex
