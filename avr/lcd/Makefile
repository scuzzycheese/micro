OPT = -Os -mcall-prologues


all:
	avr-gcc -g ${OPT} -mmcu=atmega8 -c lcdtest.c -I../avrlib -I.

	avr-gcc -g ${OPT} -mmcu=atmega8 -c lcd.c -I../avrlib -I.

	avr-gcc -g ${OPT} -mmcu=atmega8 -c i2c.c -I../avrlib -I.


	avr-gcc -g ${OPT} -mmcu=atmega8 -o lcdtest.elf lcdtest.o lcd.o i2c.o
	avr-objcopy -j .text -j .data -O ihex lcdtest.elf lcdtest.hex


install:
	avrdude -p m8 -c stk200 -e -U flash:w:lcdtest.hex

install-dragon:
	avrdude -p m8 -c dragon_isp -P usb -U flash:w:lcdtest.hex
