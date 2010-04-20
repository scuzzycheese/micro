CPU = -mmcu=atmega8
OPT = -Os -mcall-prologues
PATHS = -I.

all: radio.o ar1010.o lcd.o i2c.o

	avr-gcc ${OPT} ${CPU} -o radio.elf radio.o lcd.o ar1010.o i2c.o
	avr-objcopy -j .text -j .data -O ihex radio.elf radio.hex

lcd.o: lcd.c lcdconf.h
	avr-gcc ${OPT} ${CPU} -c lcd.c ${PATHS}

ar1010.o: ar1010.c ar1010.h
	avr-gcc ${OPT} ${CPU} -c ar1010.c ${PATHS}

i2c.o: i2c.c i2c.h
	avr-gcc ${OPT} ${CPU} -c i2c.c ${PATHS}

radio.o: radio.c
	avr-gcc ${OPT} ${CPU} -c radio.c ${PATHS}

gdb-init: all
	avr-objcopy -j .text -j .data -O binary radio.elf radio.bin

install:
	avrdude -p m8 -c stk200 -e -U flash:w:radio.hex

install-dragon:
	avrdude -p m8 -c dragon_isp -P usb -U flash:w:radio.hex

fuse:
	avrdude -p m8 -c dragon_isp -P usb -U hfuse:w:0xc9:m -U lfuse:w:0xef:m

clean:
	rm -Rf *.o
	rm -Rf *.hex
	rm -Rf *.elf