CHIP=atmega644
#DEBUG= -DDEBUGSOCK
OPT = -Os -mcall-prologues

GENPATH = -Iwebserver

UIPF = ../uip/uip/uip.c
UIPARP = ../uip/uip/uip_arp.c
#SERVICE = hello-world.c
#SERVICE = -Iwebserver webserver/httpd.c webserver/http-strings.c webserver/httpd-fs.c webserver/httpd-cgi.c
SERVICE = web2.c
PSOCK = ../uip/uip/psock.c
CLOCK = clock-arch.c
TIMER = ../uip/uip/timer.c

#===MODULES===
INDEX = webserver/oloader/index.c
INDEXO = webserver/oloader/index.o
IMAGE = webserver/oloader/image.c
IMAGEO = webserver/oloader/image.o
MODULES = ${INDEXO} ${IMAGEO}

UART = uart.c

ENC28J60 = enc28j60.c

UIPSTUFF = ${UIPF} ${UIPARP} ${PSOCK} ${CLOCK} ${TIMER}
AVRLIBSTUFF = ${ENC28J60}
UARTSTUFF = ${UART}

AVRLIBINCLUDES = -I/usr/avr/include
UIPLIBPATH = -I../uip/uip/
AVRLIBPATH = -I../avrlib/
MYPATH = -I. ${GENPATH}
LIBPATH = ${AVRLIBINCLUDES} ${UIPLIBPATH} ${AVRLIBPATH} ${MYPATH}




all:uip service avrlib uart ethernet hash dynaloader modules
	avr-gcc ${DEBUG} ${OPT} -mmcu=${CHIP} -o ethernet.elf ethernet.o uip.o avrlib.o service.o uart.o libhash/libhash.o dynaloader.o ${MODULES} -lm ${LIBPATH}

ethernet: ethernet.c
	avr-gcc ${DEBUG} ${OPT} -mmcu=${CHIP} -c ethernet.c -o ethernet.o ${LIBPATH}
uip: 
	avr-gcc ${DEBUG} ${OPT} -mmcu=${CHIP} -c -combine ${UIPSTUFF} -o uip.o ${AVRLIBINCLUDES} ${UIPLIBPATH} ${MYPATH}
service:
	avr-gcc ${DEBUG} ${OPT} -mmcu=${CHIP} -c -combine ${SERVICE} -o service.o ${AVRLIBINCLUDES} ${UIPLIBPATH} ${MYPATH}
avrlib:
	avr-gcc ${DEBUG} ${OPT} -mmcu=${CHIP} -c -combine ${AVRLIBSTUFF} -o avrlib.o ${AVRLIBINCLUDES} ${AVRLIBPATH} ${MYPATH}
uart: uart.c uart.h
	avr-gcc ${DEBUG} ${OPT} -mmcu=${CHIP} -c -combine ${UARTSTUFF} -o uart.o ${AVRLIBINCLUDES} ${MYPATH}
hash:
	avr-gcc ${DEBUG} ${OPT} -mmcu=${CHIP} -c -combine libhash/libhash.c -o libhash/libhash.o
dynaloader:
	avr-gcc ${DEBUG} ${OPT} -mmcu=${CHIP} -c -combine dynaloader.c -o dynaloader.o



modules:
	avr-gcc ${DEBUG} ${OPT} -mmcu=${CHIP} -c -combine ${INDEX} -o ${INDEXO}
	avr-gcc ${DEBUG} ${OPT} -mmcu=${CHIP} -c -combine ${IMAGE} -o ${IMAGEO}




install: ethernet.elf
	avr-objcopy -j .text -j .data -O ihex ethernet.elf ethernet.hex
	avrdude -p m644 -c stk200 -e -E noreset -U flash:w:ethernet.hex

install-dragon: ethernet.elf
	avr-objcopy -j .text -j .data -O ihex ethernet.elf ethernet.hex
	avrdude -p m644 -c dragon_isp -P usb -e -E noreset -U flash:w:ethernet.hex

clean:
	rm -Rf uip.o service.o avrlib.o uart.o ethernet.o ethernet.elf ethernet.hex libhash/libhash.o dynaloader.o ${MODULES}
