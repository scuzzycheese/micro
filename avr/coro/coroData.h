#ifndef CORODATAH
#define CORODATAH
#ifdef __AVR__
#include <avr/io.h>
#endif

//Some lovely foward declairation
struct csd;

typedef void (*fibreType)(struct csd *);

//NOTE: this is packed, to make it as small as possible
struct csd 
{
#ifdef __AVR__
#else
#endif

	char *sp;
	char *bp;

	fibreType retAdd;

	//These flags contain statuses about the fibre
	char flags;

	char *mallocStack;

	struct csd *next;
	struct csd *prev;
	struct csd *last;
} __attribute__ ((__packed__));
typedef struct csd coStData;


//define the bit fields
#define CALLSTATUS 0
#define JMPBIT 1
#define SHEDULED 2
#define FINISHED 3

//Different status depending on where we jump from
#define JMPFROMMAIN 0
#define JMPFROMROUTINE 1

//Different jump types
#define CALL 0
#define JMP 1

//this is to find the offset value of members of structs
#define OFFSET(obj,mem) (int)&(((obj *)NULL)->mem)

//some helper macros for getting and setting bits
#define SETBIT(data,field) (data |= (1 << field))
#define CLRBIT(data,field) (data &= ~(1 << field))
#define GETBIT(data,field) ((data & (1 << field)) > 0)


//This is a hopefull combination of setStack and callToAdd
#ifdef __AVR__
#define setStackAndCallToAdd(sp,add) __asm__ \
( \
	"out __SP_H__, %B0\n" \
	"out __SP_L__, %A0\n" \
	\
	"in r29, __SP_H__\n" \
	"in r28, __SP_L__\n" \
	\
	"icall\n" \
	\
	: \
	:"e"(sp),"z"(add) \
)
#else
#define setStackAndCallToAdd(sp,add) __asm__ \
( \
	"movl %%eax, %%ebp\n" \
	"movl %%eax, %%esp\n" \
	"call *%%ebx\n" \
	\
	: \
	:"a"(sp),"b"(add) \
)
#endif

#ifdef __AVR__
#define jmpToAdd(add) __asm__ \
( \
	"ijmp" \
	\
	: \
	:"z"(add) \
)
#else
#define jmpToAdd(add) __asm__ \
( \
	"jmp *%%eax" \
	\
	: \
	:"a"(add) \
)
#endif

#ifdef __AVR__
#define regSave(buf) __asm__ \
( \
	"push r0\n" \
	"push r1\n" \
	"push r2\n" \
	"push r3\n" \
	"push r4\n" \
	"push r5\n" \
	"push r6\n" \
	"push r7\n" \
	"push r8\n" \
	"push r9\n" \
	"push r10\n" \
	"push r11\n" \
	"push r12\n" \
	"push r13\n" \
	"push r14\n" \
	"push r15\n" \
	"push r16\n" \
	"push r17\n" \
	"push r18\n" \
	"push r19\n" \
	"push r20\n" \
	"push r21\n" \
	"push r22\n" \
	"push r23\n" \
	"push r24\n" \
	"push r25\n" \
	"push r26\n" \
	"push r27\n" \
	"push r28\n" \
	"push r29\n" \
	"push r30\n" \
	"push r31\n" \
	\
	"in __tmp_reg__, __SP_H__\n" \
	"st %a0+, __tmp_reg__\n" \
	"in __tmp_reg__, __SP_L__\n" \
	"st %a0+, __tmp_reg__\n" \
	\
	"st %a0+, r29\n" \
	"st %a0, r28\n" \
	\
	: \
	:"e"(buf) \
)
#else
#define regSave(buf) __asm__ \
( \
	"pushl %%ebx\n" \
	"pushl %%esi\n" \
	"pushl %%edi\n" \
	"pushl %%esp\n" \
	"pushl %%ecx\n" \
	"pushl %%ebp\n" \
	"pushl %%edx\n" \
	"movl %%esp, (%%eax)\n" \
	"movl %%ebp, (4)(%%eax)\n" \
	\
	: \
	:"a"(buf) \
)
#endif


#ifdef __AVR__
#define regRestore(buf) __asm__ \
( \
	"ld __tmp_reg__, %a0+\n" \
	"out __SP_H__, __tmp_reg__\n" \
	"ld __tmp_reg__, %a0+\n" \
	"out __SP_L__, __tmp_reg__\n" \
	\
	"ld r29, %a0+\n" \
	"ld r28, %a0\n" \
	\
	"pop r0\n" \
	"pop r1\n" \
	"pop r2\n" \
	"pop r3\n" \
	"pop r4\n" \
	"pop r5\n" \
	"pop r6\n" \
	"pop r7\n" \
	"pop r8\n" \
	"pop r9\n" \
	"pop r10\n" \
	"pop r11\n" \
	"pop r12\n" \
	"pop r13\n" \
	"pop r14\n" \
	"pop r15\n" \
	"pop r16\n" \
	"pop r17\n" \
	"pop r18\n" \
	"pop r19\n" \
	"pop r20\n" \
	"pop r21\n" \
	"pop r22\n" \
	"pop r23\n" \
	"pop r24\n" \
	"pop r25\n" \
	"pop r26\n" \
	"pop r27\n" \
	"pop r28\n" \
	"pop r29\n" \
	"pop r30\n" \
	"pop r31\n" \
	\
	: \
	:"e"(buf) \
)
#else
#define regRestore(buf) __asm__ \
( \
	"movl (%%eax), %%esp\n" \
	"movl (4)(%%eax), %%ebp\n" \
	"popl %%edx\n" \
	"popl %%ebp\n" \
	"popl %%ecx\n" \
	"popl %%esp\n" \
	"popl %%edi\n" \
	"popl %%esi\n" \
	"popl %%ebx\n" \
	\
	: \
	:"a"(buf) \
)
#endif

#ifdef __AVR__
#define regRestoreAndJmpToAdd(buf) __asm__ \
( \
	"ld __tmp_reg__, %a0+\n" \
	"out __SP_H__, __tmp_reg__\n" \
	"ld __tmp_reg__, %a0+\n" \
	"out __SP_L__, __tmp_reg__\n" \
	\
	"ld r29, %a0+\n" \
	"ld r28, %a0+\n" \
	\
	"pop r0\n" \
	"pop r1\n" \
	"pop r2\n" \
	"pop r3\n" \
	"pop r4\n" \
	"pop r5\n" \
	"pop r6\n" \
	"pop r7\n" \
	"pop r8\n" \
	"pop r9\n" \
	"pop r10\n" \
	"pop r11\n" \
	"pop r12\n" \
	"pop r13\n" \
	"pop r14\n" \
	"pop r15\n" \
	"pop r16\n" \
	"pop r17\n" \
	"pop r18\n" \
	"pop r19\n" \
	"pop r20\n" \
	"pop r21\n" \
	"pop r22\n" \
	"pop r23\n" \
	"pop r24\n" \
	"pop r25\n" \
	"pop r26\n" \
	"pop r27\n" \
	"pop r28\n" \
	"pop r29\n" \
	"pop r30\n" \
	"pop r31\n" \
	"ijmp\n" \
	\
	: \
	:"e"(buf) \
)
#else
#define regRestoreAndJmpToAdd(buf) __asm__ \
( \
	"movl (%%eax), %%esp\n" \
	"movl (4)(%%eax), %%ebp\n" \
	"popl %%edx\n" \
	"popl %%ebp\n" \
	"popl %%ecx\n" \
	"popl %%esp\n" \
	"popl %%edi\n" \
	"popl %%esi\n" \
	"popl %%ebx\n" \
	"jmp *(8)(%%eax)" \
	\
	: \
	:"a"(buf) \
)
#endif


#endif
