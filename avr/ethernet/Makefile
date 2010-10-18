CC = avr-gcc
CCX86 = gcc
CHIP = -mmcu=atmega644
#DEBUG= -DDEBUGSOCK
OPT = -g3 -O0 -mcall-prologues -std=c99
#OPT = -g -O0 -std=c99
#OPT = -mcall-prologues
OPTX86 = -O0 -g3 -DX86

GENPATH =

UIPF = ./uip/uip.c
UIPARP = ./uip/uip_arp.c
SERVICE = web3.o
PSOCK = ./uip/psock.c
CLOCK = clock-arch.c
TIMER = ./uip/timer.c


ENC28J60 = enc28j60.c

UIPSTUFF = ${UIPF} ${UIPARP} ${PSOCK} ${CLOCK} ${TIMER}
AVRLIBSTUFF = ${ENC28J60}

AVRLIBINCLUDES = -I/usr/lib/avr/include/
UIPLIBPATH = -I./uip/
AVRLIBPATH = -I../avrlib/
UARTLIBPATH = -I./uart/
MYPATH = -I. ${GENPATH} ${FIBINC}
LIBPATH = ${AVRLIBINCLUDES} ${UIPLIBPATH} ${AVRLIBPATH} ${UARTLIBPATH} ${MYPATH}

#===MODULES===
INDEX = pages/index.o
IMAGE = pages/image.o
ERROR404 = pages/404.o
MODULES = ${INDEX} ${IMAGE} ${ERROR404}


all:uip.o ${SERVICE} enc28j60 uart ethernet.o hash ${MODULES}
	${CC} ${DEBUG} ${OPT} ${CHIP} -o ethernet.elf ethernet.o uip.o enc28j60.o ${SERVICE} uart/uart.o libhash/libhash.o ${MODULES} -lm ${LIBPATH}
	avr-objcopy -j .text -j .data -O ihex ethernet.elf ethernet.hex

ethernet.o: ethernet.c
	${CC} ${DEBUG} ${OPT} ${CHIP} -c ethernet.c -o ethernet.o ${LIBPATH}

uip.o: ${UIPSTUFF} 
	${CC} ${DEBUG} ${OPT} ${CHIP} -c -combine ${UIPSTUFF} -o uip.o ${LIBPATH}

${SERVICE}: ${SERVICE:.o=.c} ${SERVICE:.o=.h}
	#don't optimise this module, otherwise it manifests a GCC bug
	${CC} ${DEBUG} ${OPT} ${CHIP} -c -combine ${SERVICE:.o=.c} -o ${SERVICE} ${LIBPATH}

enc28j60:
	${CC} ${DEBUG} ${OPT} ${CHIP} -c -combine enc28j60.c -o enc28j60.o ${LIBPATH}

uart: uart/uart.c uart/uart.h
	${CC} ${DEBUG} ${OPT} ${CHIP} -c -combine uart/uart.c -o uart/uart.o ${LIBPATH}

hash: libhash/libhash.c libhash/libhash.h
	#don't optimise this module, otherwise it manifests a GCC bug
	${CC} ${DEBUG} ${CHIP} -c -combine libhash/libhash.c -o libhash/libhash.o ${LIBPATH}

#build all our web pages
${MODULES}: ${@:.o=.c} ${@:.o=.h}
	${CC} ${DEBUG} ${OPT} ${CHIP} -c -combine ${@:.o=.c} -o $@ ${LIBPATH}







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
	avrdude -p m644 -c stk200 -e -E noreset -U flash:w:ethernet.hex

install-dragon: ethernet.elf
	avrdude -B9 -p m644 -c dragon_isp -P usb -e -U flash:w:ethernet.hex

install-dragon-jtag: ethernet.elf
	avrdude -B9 -p m644 -c dragon_jtag -P usb -e -U flash:w:ethernet.hex

fuse:
	avrdude -p m644 -c dragon_isp -P usb -e -U hfuse:w:0x11:m -U lfuse:w:0xEF:m
	#avrdude -p m644 -c dragon_isp -P usb -e -U lfuse:w:0xff:m -U hfuse:w:0x99:m -U efuse:w:0xff:m

reset:
	avrdude -p m644 -c dragon_isp -P usb -n

clean:
	rm -Rf uip.o ${SERVICE} avrlib.o uart/uart.o ethernet.o ethernet ethernet.elf ethernet.hex libhash/libhash.o ${MODULES}
