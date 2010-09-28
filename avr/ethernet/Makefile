CC = avr-gcc
CCX86 = gcc
CHIP = -mmcu=atmega644
#DEBUG= -DDEBUGSOCK
OPT = -Os -mcall-prologues -std=c99
#OPT = -mcall-prologues
OPTX86 = -O0 -g3 -DX86

GENPATH =

UIPF = ../uip/uip/uip.c
UIPARP = ../uip/uip/uip_arp.c
#SERVICE = hello-world.c
#SERVICE = -Iwebserver webserver/httpd.c webserver/http-strings.c webserver/httpd-fs.c webserver/httpd-cgi.c
#SERVICE = web2.o
SERVICE = web3.o
PSOCK = ../uip/uip/psock.c
CLOCK = clock-arch.c
TIMER = ../uip/uip/timer.c

UART = uart.c

ENC28J60 = enc28j60.c

UIPSTUFF = ${UIPF} ${UIPARP} ${PSOCK} ${CLOCK} ${TIMER}
AVRLIBSTUFF = ${ENC28J60}
UARTSTUFF = ${UART}

AVRLIBINCLUDES = -I/usr/lib/avr/include/
UIPLIBPATH = -I../uip/uip/
AVRLIBPATH = -I../avrlib/
MYPATH = -I. ${GENPATH} ${FIBINC}
LIBPATH = ${AVRLIBINCLUDES} ${UIPLIBPATH} ${AVRLIBPATH} ${MYPATH}

#===MODULES===
INDEX = pages/index.o
IMAGE = pages/image.o
ERROR404 = pages/404.o
MODULES = ${INDEX} ${IMAGE} ${ERROR404}


all:uip.o ${SERVICE} avrlib uart ethernet.o hash ${MODULES}
	${CC} ${DEBUG} ${OPT} ${CHIP} -o ethernet.elf ethernet.o uip.o avrlib.o ${SERVICE} uart.o libhash/libhash.o ${MODULES} -lm ${LIBPATH}

ethernet.o: ethernet.c
	${CC} ${DEBUG} ${OPT} ${CHIP} -c ethernet.c -o ethernet.o ${LIBPATH}

#this one is complex, and maybe needs all the dependancies figured out
uip.o: ${UIPSTUFF} 
	${CC} ${DEBUG} ${OPT} ${CHIP} -c -combine ${UIPSTUFF} -o uip.o ${AVRLIBINCLUDES} ${UIPLIBPATH} ${MYPATH}

${SERVICE}: ${SERVICE:.o=.c} ${SERVICE:.o=.h}
	#don't optimise this module, otherwise it manifests a GCC bug
	${CC} ${DEBUG} ${CHIP} -c -combine ${SERVICE:.o=.c} -o ${SERVICE} ${AVRLIBINCLUDES} ${UIPLIBPATH} ${MYPATH}

avrlib:
	${CC} ${DEBUG} ${OPT} ${CHIP} -c -combine ${AVRLIBSTUFF} -o avrlib.o ${AVRLIBINCLUDES} ${AVRLIBPATH} ${MYPATH}

uart: uart.c uart.h
	${CC} ${DEBUG} ${OPT} ${CHIP} -c -combine ${UARTSTUFF} -o uart.o ${AVRLIBINCLUDES} ${MYPATH}

hash: libhash/libhash.c libhash/libhash.h
	#don't optimise this module, otherwise it manifests a GCC bug
	${CC} ${DEBUG} ${CHIP} -c -combine libhash/libhash.c -o libhash/libhash.o ${MYPATH}

#build all our web pages
${MODULES}: ${@:.o=.c} ${@:.o=.h}
	${CC} ${DEBUG} ${OPT} ${CHIP} -c -combine ${@:.o=.c} -o $@ ${LIBPATH}







x86:uip-x86 service-x86 uart-x86 ethernet-x86 hash-x86 modules-x86 
	${CCX86} ${DEBUG} ${OPTX86} -o ethernet ethernet.o uip.o service.o uart.o libhash/libhash.o pages/index-x86.o pages/404-x86.o -lm

ethernet-x86: ethernet.c
	${CCX86} ${DEBUG} ${OPTX86} -c ethernet.c -o ethernet.o ${UIPLIBPATH} ${MYPATH}
uip-x86: 
	${CCX86} ${DEBUG} ${OPTX86} -c -combine ${UIPSTUFF} -o uip.o ${UIPLIBPATH} ${MYPATH}
service-x86:
	${CCX86} ${DEBUG} ${OPTX86} -c -combine ${SERVICE:.o=.c} -o service.o ${UIPLIBPATH} ${MYPATH}
uart-x86: uart.c uart.h
	${CCX86} ${DEBUG} ${OPTX86} -c -combine ${UARTSTUFF} -o uart.o ${MYPATH}
hash-x86:
	${CCX86} ${DEBUG} ${OPTX86} -c -combine libhash/libhash.c -o libhash/libhash.o ${MYPATH}

modules-x86:
	${CCX86} ${DEBUG} ${OPTX86} -c -combine pages/index-x86.c -o pages/index-x86.o ${UIPLIBPATH} ${MYPATH}
	${CCX86} ${DEBUG} ${OPTX86} -c -combine pages/404.c -o pages/404-x86.o ${UIPLIBPATH} ${MYPATH}





install: ethernet.elf
	avr-objcopy -j .text -j .data -O ihex ethernet.elf ethernet.hex
	avrdude -p m644 -c stk200 -e -E noreset -U flash:w:ethernet.hex

install-dragon: ethernet.elf
	avr-objcopy -j .text -j .data -O ihex ethernet.elf ethernet.hex
	avrdude -B9 -p m644 -c dragon_isp -P usb -e -U flash:w:ethernet.hex

fuse:
	avrdude -p m644 -c dragon_isp -P usb -e -U hfuse:w:0x91:m -U lfuse:w:0xEF:m
	#avrdude -p m644 -c dragon_isp -P usb -e -U lfuse:w:0xff:m -U hfuse:w:0x99:m -U efuse:w:0xff:m

reset:
	avrdude -p m644 -c dragon_isp -P usb -n

clean:
	rm -Rf uip.o ${SERVICE} avrlib.o uart.o ethernet.o ethernet ethernet.elf ethernet.hex libhash/libhash.o ${MODULES}
