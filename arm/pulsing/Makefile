# Our tools.
CC      = arm-elf-gcc
LD      = arm-elf-ld
AS      = arm-elf-as
CP      = arm-elf-objcopy

# Commandline options for each tool.
CFLAGS  = -I./ -c -fno-common -O0 -g -std=c99
AFLAGS  = -ahls -mapcs-32 -o crt.o
LFLAGS  = -v -Map blink.map -Tram-ln.cmd
CPFLAGS = --output-target=binary

# Our target.
all: blink.hex

clean:
	rm -f *.o *.hex *.elf *.map *.lst *.bin core *~

install:
	EXECSIZE=`ls -al blink.bin | awk '{ print $5 }'`; sam7 --exec "sf 0 /home/scuzzy/Desktop/ARMBlinkExample/blink.bin 0 $${EXECSIZE}" --exec "go 0x202000"


# Convert ELF binary to Intel HEX file.
blink.hex: blink.elf
	$(CP) $(CPFLAGS) blink.elf blink.bin

# Link - this produces an ELF binary.
blink.elf: blink.o crt.o
	$(LD) $(LFLAGS) -o blink.elf crt.o blink.o

# Compile the C runtime.
crt.o: ram-crt.s
	$(AS) $(AFLAGS) ram-crt.s > crt.lst

# Compile the main program.
blink.o: blink.c
	$(CC) $(CFLAGS) -c blink.c

