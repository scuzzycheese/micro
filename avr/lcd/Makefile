CPU = -mmcu=atmega8
OPT = -Os -mcall-prologues

all: lcdtest.o ar1010.o lcd.o i2c.o

	avr-gcc ${OPT} ${CPU} -o lcdtest.elf lcdtest.o lcd.o i2c.o ar1010.o
	avr-objcopy -j .text -j .data -O ihex lcdtest.elf lcdtest.hex

i2c.o: i2c.c i2c.h i2cconf.h
	avr-gcc ${OPT} ${CPU} -c i2c.c -I../avrlib -I.

lcd.o: lcd.c lcdconf.h
	avr-gcc ${OPT} ${CPU} -c lcd.c -I../avrlib -I.

ar1010.o: ar1010.c ar1010.h
	avr-gcc ${OPT} ${CPU} -c ar1010.c -I../avrlib -I.

lcdtest.o: lcdtest.c 
	avr-gcc ${OPT} ${CPU} -c lcdtest.c -I../avrlib -I.

gdb-init: all
	avr-objcopy -j .text -j .data -O binary lcdtest.elf lcdtest.bin

install:
	avrdude -p m8 -c stk200 -e -U flash:w:lcdtest.hex

install-dragon:
	avrdude -p m8 -c dragon_isp -P usb -U flash:w:lcdtest.hex

fuse:
	avrdude -p m8 -c dragon_isp -P usb -U hfuse:w:0xc9:m -U lfuse:w:0xef:m

clean:
	rm -Rf *.o
	rm -Rf *.hex
	rm -Rf *.elf