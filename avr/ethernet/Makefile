CC = avr-gcc
CCX86 = gcc
CHIP = -mmcu=atmega644p
#DEBUG= -DDEBUGSOCK
DEBUG= 
#OPT = -Os -mcall-prologues
OPT = -mcall-prologues
OPTX86 = -g3 -DX86

GENPATH =

UIPF = ../uip/uip/uip.c
UIPARP = ../uip/uip/uip_arp.c
#SERVICE = hello-world.c
#SERVICE = -Iwebserver webserver/httpd.c webserver/http-strings.c webserver/httpd-fs.c webserver/httpd-cgi.c
SERVICE = web2.c
PSOCK = ../uip/uip/psock.c
CLOCK = clock-arch.c
TIMER = ../uip/uip/timer.c


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

#===MODULES===
INDEX = pages/index.c
INDEXO = pages/index.o
IMAGE = pages/image.c
IMAGEO = pages/image.o
MODULES = ${INDEXO} ${IMAGEO}


all:uip service avrlib uart ethernet hash modules
	${CC} ${DEBUG} ${OPT} ${CHIP} -o ethernet.elf ethernet.o uip.o avrlib.o service.o uart.o libhash/libhash.o ${MODULES} -lm ${LIBPATH}

ethernet: ethernet.c
	${CC} ${DEBUG} ${OPT} ${CHIP} -c ethernet.c -o ethernet.o ${LIBPATH}
uip: 
	${CC} ${DEBUG} ${OPT} ${CHIP} -c -combine ${UIPSTUFF} -o uip.o ${AVRLIBINCLUDES} ${UIPLIBPATH} ${MYPATH}
service:
	${CC} ${DEBUG} ${OPT} ${CHIP} -c -combine ${SERVICE} -o service.o ${AVRLIBINCLUDES} ${UIPLIBPATH} ${MYPATH}
avrlib:
	${CC} ${DEBUG} ${OPT} ${CHIP} -c -combine ${AVRLIBSTUFF} -o avrlib.o ${AVRLIBINCLUDES} ${AVRLIBPATH} ${MYPATH}
uart: uart.c uart.h
	${CC} ${DEBUG} ${OPT} ${CHIP} -c -combine ${UARTSTUFF} -o uart.o ${AVRLIBINCLUDES} ${MYPATH}
hash:
	${CC} ${DEBUG} ${OPT} ${CHIP} -c -combine libhash/libhash.c -o libhash/libhash.o ${MYPATH}

modules:
	${CC} ${DEBUG} ${OPT} ${CHIP} -c -combine ${INDEX} -o ${INDEXO} ${LIBPATH}
	${CC} ${DEBUG} ${OPT} ${CHIP} -c -combine ${IMAGE} -o ${IMAGEO} ${LIBPATH}

x86:uip-x86 service-x86 uart-x86 ethernet-x86 hash-x86 modules-x86
	${CCX86} ${DEBUG} ${OPTX86} ${CHIP} -o ethernet ethernet.o uip.o service.o uart.o libhash/libhash.o pages/index.o -lm 

ethernet-x86: ethernet.c
	${CCX86} ${DEBUG} ${OPTX86} -c ethernet.c -o ethernet.o ${UIPLIBPATH} ${MYPATH}
uip-x86: 
	${CCX86} ${DEBUG} ${OPTX86} -c -combine ${UIPSTUFF} -o uip.o ${UIPLIBPATH} ${MYPATH}
service-x86:
	${CCX86} ${DEBUG} ${OPTX86} -c -combine ${SERVICE} -o service.o ${UIPLIBPATH} ${MYPATH}
uart-x86: uart.c uart.h
	${CCX86} ${DEBUG} ${OPTX86} -c -combine ${UARTSTUFF} -o uart.o ${MYPATH}
hash-x86:
	${CCX86} ${DEBUG} ${OPTX86} -c -combine libhash/libhash.c -o libhash/libhash.o ${MYPATH}

modules-x86:
	${CCX86} ${DEBUG} ${OPTX86} -c -combine pages/index-x86.c -o ${INDEXO} ${UIPLIBPATH} ${MYPATH} 


install: ethernet.elf
	avr-objcopy -j .text -j .data -O ihex ethernet.elf ethernet.hex
	avrdude -y -p m644 -c stk200 -e -E noreset -U flash:w:ethernet.hex

install-dragon: ethernet.elf
	avr-objcopy -j .text -j .data -O ihex ethernet.elf ethernet.hex
	avrdude -y -p m644p -c dragon_isp -P usb -e -U flash:w:ethernet.hex

clean:
	rm -Rf uip.o service.o avrlib.o uart.o ethernet.o ethernet ethernet.elf ethernet.hex libhash/libhash.o ${MODULES}
