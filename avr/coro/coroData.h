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
	uint8_t r0;
	uint8_t r1;
	uint8_t r2;
	uint8_t r3;
	uint8_t r4;
	uint8_t r5;
	uint8_t r6;
	uint8_t r7;
	uint8_t r8;
	uint8_t r9;
	uint8_t r10;
	uint8_t r11;
	uint8_t r12;
	uint8_t r13;
	uint8_t r14;
	uint8_t r15;
	uint8_t r16;
	uint8_t r17;
	uint8_t r18;
	uint8_t r19;
	uint8_t r20;
	uint8_t r21;
	uint8_t r22;
	uint8_t r23;
	uint8_t r24;
	uint8_t r25;
	uint8_t r26;
	uint8_t r27;
	uint8_t r28;
	uint8_t r29;
	uint8_t r30;
	uint8_t r31;
#else
#endif

	char *sp;
	char *bp;

	void *retAdd;

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
	"out __SP_L, %A0\n" \
	"out __SP_H, %B0\n" \
	"in r28, __SP_L__\n" \
	"in r29, __SP_H__\n" \
	"icall\n" \
	\
	: \
	:"r"(sp),"z"(add) \
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
#define setStack(sp) __asm__ \
( \
	"in r28, __SP_L__\n" \
	"in r29, __SP_H__\n" \
	\
	: \
	:"q"(sp) \
)
#else
#define setStack(sp) __asm__ \
( \
	"movl %%eax, %%ebp\n" \
	"movl %%eax, %%esp\n" \
	\
	: \
	:"a"(sp) \
)
#endif

#ifdef __AVR__
#define callToAdd(add) __asm__ \
( \
	"icall\n" \
	: \
	:"z"(add) \
)
#else
#define callToAdd(add) __asm__ \
( \
	"call *%%eax" \
	\
	: \
	:"a"(add) \
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
	"st %a0+, r0\n" \
	"st %a0+, r1\n" \
	"st %a0+, r2\n" \
	"st %a0+, r3\n" \
	"st %a0+, r4\n" \
	"st %a0+, r5\n" \
	"st %a0+, r6\n" \
	"st %a0+, r7\n" \
	"st %a0+, r8\n" \
	"st %a0+, r9\n" \
	"st %a0+, r10\n" \
	"st %a0+, r11\n" \
	"st %a0+, r12\n" \
	"st %a0+, r13\n" \
	"st %a0+, r14\n" \
	"st %a0+, r15\n" \
	"st %a0+, r16\n" \
	"st %a0+, r17\n" \
	"st %a0+, r18\n" \
	"st %a0+, r19\n" \
	"st %a0+, r20\n" \
	"st %a0+, r21\n" \
	"st %a0+, r22\n" \
	"st %a0+, r23\n" \
	"st %a0+, r24\n" \
	"st %a0+, r25\n" \
	"st %a0+, r26\n" \
	"st %a0+, r27\n" \
	"st %a0+, r28\n" \
	"st %a0+, r29\n" \
	"st %a0+, r30\n" \
	"st %a0+, r31\n" \
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
	"ld r0, %a0+\n" \
	"ld r1, %a0+\n" \
	"ld r2, %a0+\n" \
	"ld r3, %a0+\n" \
	"ld r4, %a0+\n" \
	"ld r5, %a0+\n" \
	"ld r6, %a0+\n" \
	"ld r7, %a0+\n" \
	"ld r8, %a0+\n" \
	"ld r9, %a0+\n" \
	"ld r10, %a0+\n" \
	"ld r11, %a0+\n" \
	"ld r12, %a0+\n" \
	"ld r13, %a0+\n" \
	"ld r14, %a0+\n" \
	"ld r15, %a0+\n" \
	"ld r16, %a0+\n" \
	"ld r17, %a0+\n" \
	"ld r18, %a0+\n" \
	"ld r19, %a0+\n" \
	"ld r20, %a0+\n" \
	"ld r21, %a0+\n" \
	"ld r22, %a0+\n" \
	"ld r23, %a0+\n" \
	"ld r24, %a0+\n" \
	"ld r25, %a0+\n" \
	"ld r26, %a0+\n" \
	"ld r27, %a0+\n" \
	"ld r28, %a0+\n" \
	"ld r29, %a0+\n" \
	"ld r30, %a0+\n" \
	"ld r31, %a0+\n" \
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
	"ld r0, %a0+\n" \
	"ld r1, %a0+\n" \
	"ld r2, %a0+\n" \
	"ld r3, %a0+\n" \
	"ld r4, %a0+\n" \
	"ld r5, %a0+\n" \
	"ld r6, %a0+\n" \
	"ld r7, %a0+\n" \
	"ld r8, %a0+\n" \
	"ld r9, %a0+\n" \
	"ld r10, %a0+\n" \
	"ld r11, %a0+\n" \
	"ld r12, %a0+\n" \
	"ld r13, %a0+\n" \
	"ld r14, %a0+\n" \
	"ld r15, %a0+\n" \
	"ld r16, %a0+\n" \
	"ld r17, %a0+\n" \
	"ld r18, %a0+\n" \
	"ld r19, %a0+\n" \
	"ld r20, %a0+\n" \
	"ld r21, %a0+\n" \
	"ld r22, %a0+\n" \
	"ld r23, %a0+\n" \
	"ld r24, %a0+\n" \
	"ld r25, %a0+\n" \
	"ld r26, %a0+\n" \
	"ld r27, %a0+\n" \
	"ld r28, %a0+\n" \
	"ld r29, %a0+\n" \
	"ld r30, %a0+\n" \
	"ld r31, %a0+\n" \
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
