CC = avr-gcc
CCX86 = gcc
CHIP = -mmcu=atmega644
#DEBUG= -DDEBUGSOCK
OPT = -g3 -O0 -mcall-prologues -std=c99
SEMIOPT = -g3 -O0 -mcall-prologues -std=c99
#OPT = -g -O0 -std=c99
#OPT = -mcall-prologues
OPTX86 = -O0 -g3 -DX86

GENPATH =

UIPF = ./uip/uip.c
UIPARP = ./uip/uip_arp.c
PSOCK = ./uip/psock.c
CLOCK = clock-arch.c
TIMER = ./uip/timer.c

UIPSTUFF = ${UIPF} ${UIPARP} ${PSOCK} ${CLOCK} ${TIMER}

AVRLIBINCLUDES = -I/usr/lib/avr/include/
UIPLIBPATH = -I./uip/
AVRLIBPATH = -I../avrlib/
UARTLIBPATH = -I./libuart/
WEBSERVERPATH = -I./webserver
MYPATH = -I. ${GENPATH} ${FIBINC}
LIBPATH = ${AVRLIBINCLUDES} ${UIPLIBPATH} ${AVRLIBPATH} ${UARTLIBPATH} ${WEBSERVERPATH} ${MYPATH}

#===MODULES===
INDEX = webserver/pages/index.o
IMAGE = webserver/pages/image.o
ERROR404 = webserver/pages/404.o
MODULES = ${INDEX} ${IMAGE} ${ERROR404}

#driver
ifeq "$(MAKECMDGOALS)" "enc"
DRIVER = ENC28J60
else
DRIVER = CP2200
endif


all: silabs


silabs:uip.o websrv cp2200 uart hash
	${CC} ${DEBUG} ${OPT} ${CHIP} -o ethernet.elf -combine ethernet.c uip.o cp2200.o webserver/webserver.o libuart/libuart.o libhash/libhash.o -lm ${LIBPATH} -D${DRIVER}
	avr-objcopy -j .text -j .data -O ihex ethernet.elf ethernet.hex

enc:uip.o websrv enc28j60 uart hash
	${CC} ${DEBUG} ${OPT} ${CHIP} -o ethernet.elf -combine ethernet.c uip.o enc28j60.o webserver/webserver.o libuart/libuart.o libhash/libhash.o -lm ${LIBPATH} -D${DRIVER}
	avr-objcopy -j .text -j .data -O ihex ethernet.elf ethernet.hex



uip.o: ${UIPSTUFF} 
	${CC} ${DEBUG} ${OPT} ${CHIP} -c -combine ${UIPSTUFF} -o uip.o ${LIBPATH}

websrv: webserver/web.c webserver/web.h ${MODULES}
	${CC} ${DEBUG} ${SEMIOPT} ${CHIP} -c -combine webserver/web.c -o webserver/web.o ${LIBPATH}
	avr-ld -r webserver/web.o ${MODULES} -o webserver/webserver.o

enc28j60:
	${CC} ${DEBUG} ${OPT} ${CHIP} -c -combine enc28j60.c -o enc28j60.o ${LIBPATH}

cp2200:
	${CC} ${DEBUG} ${OPT} ${CHIP} -c -combine CP2200.c -o cp2200.o ${LIBPATH}

uart: libuart/uart.c libuart/uart.h
	${CC} ${DEBUG} ${OPT} ${CHIP} -c -combine libuart/uart.c -o libuart/libuart.o ${LIBPATH}

hash: libhash/libhash.c libhash/libhash.h
	#don't optimise this module, otherwise it manifests a GCC bug
	${CC} ${DEBUG} ${CHIP} -c -combine libhash/libhash.c -o libhash/libhash.o ${LIBPATH}

#build all our web pages
${MODULES}: ${@:.o=.c} ${@:.o=.h}
	${CC} ${DEBUG} ${OPT} ${CHIP} -c -combine ${@:.o=.c} -o $@ ${LIBPATH} -D${DRIVER}







x86:uip-x86 service-x86 uart-x86 ethernet-x86 hash-x86 modules-x86 
	${CCX86} ${DEBUG} ${OPTX86} -o ethernet ethernet.o uip.o service.o uart/uart.o libhash/libhash.o pages/index-x86.o pages/404-x86.o -lm

ethernet-x86: ethernet.c
	${CCX86} ${DEBUG} ${OPTX86} -c ethernet.c -o ethernet.o ${UIPLIBPATH} ${MYPATH}
uip-x86: 
	${CCX86} ${DEBUG} ${OPTX86} -c -combine ${UIPSTUFF} -o uip.o ${UIPLIBPATH} ${MYPATH}
service-x86:
	${CCX86} ${DEBUG} ${OPTX86} -c -combine ${SERVICE:.o=.c} -o service.o ${UIPLIBPATH} ${MYPATH}
uart-x86: uart/uart.c uart/uart.h
	${CCX86} ${DEBUG} ${OPTX86} -c -combine ${UARTSTUFF} -o uart/uart.o ${MYPATH}
hash-x86:
	${CCX86} ${DEBUG} ${OPTX86} -c -combine libhash/libhash.c -o libhash/libhash.o ${MYPATH}

modules-x86:
	${CCX86} ${DEBUG} ${OPTX86} -c -combine pages/index-x86.c -o pages/index-x86.o ${UIPLIBPATH} ${MYPATH}
	${CCX86} ${DEBUG} ${OPTX86} -c -combine pages/404.c -o pages/404-x86.o ${UIPLIBPATH} ${MYPATH}





install: ethernet.elf
	avrdude -p m644p -c dragon_isp -P usb -e -U flash:w:ethernet.hex

install-dragon-jtag: ethernet.elf
	avrdude -B9 -p m644 -c dragon_jtag -P usb -e -U flash:w:ethernet.hex

fuse:
	avrdude -p m644 -c dragon_isp -P usb -e -U hfuse:w:0x11:m -U lfuse:w:0xEF:m
	#avrdude -p m644 -c dragon_isp -P usb -e -U lfuse:w:0xff:m -U hfuse:w:0x99:m -U efuse:w:0xff:m

reset:
	avrdude -p m644p -c dragon_isp -P usb -n

reset-jtag:
	avrdude -p m644 -c dragon_jtag -P usb -n

clean:
	rm -Rf enc28j60.o CP2200.o uip.o webserver/web.o webserver/webserver.o avrlib.o uart/uart.o ethernet.o ethernet ethernet.elf ethernet.hex libhash/libhash.o ${MODULES}

debug:
	avarice -f ethernet.hex -j usb -g -e -p :1234
