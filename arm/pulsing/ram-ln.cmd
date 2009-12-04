/*
   Linker options for loading a program in RAM on the AT91SAM7S256
   This goes with ram-crt.s
   by Adam Pierce http://www.doctort.org/adam

   I'm assuming here that the SAM-BA leaves the system in user mode with a
   stack and everything already configured.

   The AT91SAM7S256 has RAM starting from 0x00200000 to 0x0020FFFF. SAM-BA reserves
   some of that so we have a usable range of 0x00202000 to 0x0020FFFF.

*/

/* Define the entry point of the program */
ENTRY(_init)

/* RAM address range for the AT91SAM7S256 minus the amount used by SAM-BA */
MEMORY 
{
	ram : ORIGIN = 0x00202000, LENGTH = 56K
}

/* Map all the sections used by the C compiler to RAM */
SECTIONS
{
	.text : /* The .text section is where the C compiler will put it's code */
	{
		/* *(.glue_7)   The glue sections are required by the linker for it's own */
		/* *(.glue_7t)  internal weirdness. */
		_text = .;
		_etext = .;
	} >ram

	.data :	/* The .data section is for C constants and initialised variables */
	{
		_data = .;
		_edata = .;
	} >ram

	.rodata : /* section in the data for a .rodata (read only data) */
	{
		_rodata = .;
		_erodata = .;
	} >ram

	.bss :	/* The .bss section is for C variables */
	{
		_bss_start = .;					/* define a global symbol marking the start of the .bss section */
	} >ram								/* put all the above in RAM (it will be cleared in the startup code */


	_bss_end = . ;						/* define a global symbol marking the end of the .bss section */
}
	
