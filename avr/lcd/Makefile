CPU = -mmcu=atmega8
OPT = -g -Os -mcall-prologues -Wl,-Map,lcdtest.map
//OPT = -mcall-prologues

all:
	avr-gcc ${OPT} ${CPU} -c lcdtest.c -I../avrlib -I.

	avr-gcc ${OPT} ${CPU} -c lcd.c -I../avrlib -I.

	avr-gcc ${OPT} ${CPU} -c i2c.c -I../avrlib -I.


	avr-gcc ${OPT} ${CPU} -o lcdtest.elf lcdtest.o lcd.o i2c.o
	avr-objcopy -j .text -j .data -O ihex lcdtest.elf lcdtest.hex

gdb-init: all
	avr-objcopy -j .text -j .data -O binary lcdtest.elf lcdtest.bin

install:
	avrdude -p m8 -c stk200 -e -U flash:w:lcdtest.hex

install-dragon:
	avrdude -p m8 -c dragon_isp -P usb -U flash:w:lcdtest.hex

fuse:
	avrdude -p m8 -c dragon_isp -P usb -U hfuse:w:0xc9:m -U lfuse:w:0xef:m
