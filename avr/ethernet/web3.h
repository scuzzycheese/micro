#ifndef WEB3H
#define WEB3H

#include "uipopt.h"
#include "config.h"

#ifdef __AVR__
#include <avr/io.h>
#endif

#define ISO_nl       0x0a
#define ISO_space    0x20
#define ISO_bang     0x21
#define ISO_percent  0x25
#define ISO_period   0x2e
#define ISO_slash    0x2f
#define ISO_colon    0x3a
#define ISO_question 0x3f
#define ISO_equals   0x3d
#define ISO_amp      0x26

//Some lovely foward declairation
struct csd;

typedef void (*fibreType)(void);

//NOTE: this is packed, to make it as small as possible
struct csd
{

	char *sp;
#ifdef X86
	char *bp;
#endif

	fibreType retAdd;

	//These flags contain statuses about the fibre
	char flags;

	char *mallocStack;
} __attribute__ ((__packed__));
typedef struct csd coStData;
typedef struct csd uip_tcp_appstate_t;


//define the bit fields
#define CALLSTATUS 0
#define JMPBIT 1
#define SHEDULED 2
#define FINISHED 3

//Different status depending on where we jump from
#define JMPFROMMAIN 0
#define JMPFROMROUTINE 2

//Different jump types
#define CALL 0
#define JMP 1

//this is to find the offset value of members of structs
#define OFFSET(obj,mem) (int)&(((obj *)NULL)->mem)

//some helper macros for getting and setting bits
#define SETBIT(data,field) (data |= (1 << field))
#define CLRBIT(data,field) (data &= ~(1 << field))
#define GETBIT(data,field) (data & (1 << field))


//This is a hopefull combination of setStack and callToAdd
#ifdef __AVR__
#define setStackAndCallToAdd(sp,add) __asm__ volatile \
( \
	"out __SP_H__, %B0\n" \
	"out __SP_L__, %A0\n" \
	\
	"icall\n" \
	\
	: \
	:"e"(sp),"z"(add) \
)
#elif defined(X86)
#define setStackAndCallToAdd(sp,add) __asm__  \
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
#define jmpToAdd(add) __asm__ volatile \
( \
	"ijmp" \
	\
	: \
	:"z"(add) \
)
#elif defined(X86)
#define jmpToAdd(add) __asm__ \
( \
	"jmp *%%eax" \
	\
	: \
	:"a"(add) \
)
#endif
#ifdef __AVR__
#define regSaveAndJumpToMain(buf) __asm__ volatile \
( \
	"push r0\n" \
	"in r0, __SREG__\n" \
	"cli\n" \
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
	"in __tmp_reg__, __SP_L__\n" \
	"st %a0+, __tmp_reg__\n" \
	"in __tmp_reg__, __SP_H__\n" \
	"st %a0, __tmp_reg__\n" \
	\
	"sei\n" \
	\
	"rjmp MAINRET\n" \
	: \
	:"e"(buf) \
)
#elif defined(X86)
#define regSaveAndJumpToMain(buf) __asm__ \
( \
	"pushl %%eax\n" \
	"pushl %%ebx\n" \
	"pushl %%esi\n" \
	"pushl %%edi\n" \
	"pushl %%esp\n" \
	"pushl %%ecx\n" \
	"pushl %%ebp\n" \
	"pushl %%edx\n" \
	"movl %%esp, (%%eax)\n" \
	\
	"jmp MAINRET\n" \
	\
	: \
	:"a"(buf) \
)
#endif

#ifdef __AVR__
#define regSave(buf) __asm__ volatile \
( \
	"push r0\n" \
	"in r0, __SREG__\n" \
	"cli\n" \
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
	"in __tmp_reg__, __SP_L__\n" \
	"st %a0+, __tmp_reg__\n" \
	"in __tmp_reg__, __SP_H__\n" \
	"st %a0, __tmp_reg__\n" \
	\
	"sei\n" \
	\
	: \
	:"e"(buf) \
)
#elif defined(X86)
#define regSave(buf) __asm__ \
( \
	"pushl %%eax\n" \
	"pushl %%ebx\n" \
	"pushl %%esi\n" \
	"pushl %%edi\n" \
	"pushl %%esp\n" \
	"pushl %%ecx\n" \
	"pushl %%ebp\n" \
	"pushl %%edx\n" \
	"movl %%esp, (%%eax)\n" \
	\
	: \
	:"a"(buf) \
)
#endif


#ifdef __AVR__
#define regRestore(buf) __asm__ volatile \
( \
	"ld __tmp_reg__, %a0+\n" \
	"out __SP_L__, __tmp_reg__\n" \
	"ld __tmp_reg__, %a0\n" \
	"out __SP_H__, __tmp_reg__\n" \
	\
	"pop r31\n" \
	"pop r30\n" \
	"pop r29\n" \
	"pop r28\n" \
	"pop r27\n" \
	"pop r26\n" \
	"pop r25\n" \
	"pop r24\n" \
	"pop r23\n" \
	"pop r22\n" \
	"pop r21\n" \
	"pop r20\n" \
	"pop r19\n" \
	"pop r18\n" \
	"pop r17\n" \
	"pop r16\n" \
	"pop r15\n" \
	"pop r14\n" \
	"pop r13\n" \
	"pop r12\n" \
	"pop r11\n" \
	"pop r10\n" \
	"pop r9\n" \
	"pop r8\n" \
	"pop r7\n" \
	"pop r6\n" \
	"pop r5\n" \
	"pop r4\n" \
	"pop r3\n" \
	"pop r2\n" \
	"pop r1\n" \
	"pop r0\n" \
	"out __SREG__, r0\n" \
	"pop r0\n" \
	\
	: \
	:"e"(buf) \
)
#elif defined(X86)
#define regRestore(buf) __asm__ \
( \
	"movl (%%eax), %%esp\n" \
	"popl %%edx\n" \
	"popl %%ebp\n" \
	"popl %%ecx\n" \
	"popl %%esp\n" \
	"popl %%edi\n" \
	"popl %%esi\n" \
	"popl %%ebx\n" \
	"popl %%eax\n" \
	\
	: \
	:"a"(buf) \
)
#endif

#ifdef __AVR__
#define regRestoreAndJmpToYeild(buf) __asm__ volatile \
( \
	"ld __tmp_reg__, %a0+\n" \
	"out __SP_L__, __tmp_reg__\n" \
	"ld __tmp_reg__, %a0\n" \
	"out __SP_H__, __tmp_reg__\n" \
	\
	"pop r31\n" \
	"pop r30\n" \
	"pop r29\n" \
	"pop r28\n" \
	"pop r27\n" \
	"pop r26\n" \
	"pop r25\n" \
	"pop r24\n" \
	"pop r23\n" \
	"pop r22\n" \
	"pop r21\n" \
	"pop r20\n" \
	"pop r19\n" \
	"pop r18\n" \
	"pop r17\n" \
	"pop r16\n" \
	"pop r15\n" \
	"pop r14\n" \
	"pop r13\n" \
	"pop r12\n" \
	"pop r11\n" \
	"pop r10\n" \
	"pop r9\n" \
	"pop r8\n" \
	"pop r7\n" \
	"pop r6\n" \
	"pop r5\n" \
	"pop r4\n" \
	"pop r3\n" \
	"pop r2\n" \
	"pop r1\n" \
	"pop r0\n" \
	"out __SREG__, r0\n" \
	"pop r0\n" \
	"rjmp FIBRET\n" \
	\
	: \
	:"e"(buf) \
)
#elif defined(X86)
#define regRestoreAndJmpToYeild(buf) __asm__ \
( \
	"movl (%%eax), %%esp\n" \
	"popl %%edx\n" \
	"popl %%ebp\n" \
	"popl %%ecx\n" \
	"popl %%esp\n" \
	"popl %%edi\n" \
	"popl %%esi\n" \
	"popl %%ebx\n" \
	"popl %%eax\n" \
	"jmp FIBRET" \
	\
	: \
	:"a"(buf) \
)
#endif


__volatile__ static coStData mainRegs;
void fibre_yield(coStData *rt) __attribute__((noinline));
void fibre_create(coStData *regs, fibreType rAdd, int stackSize, char *stackPointer);
void fibres_start();
void preUIpInit();




void web_appcall(void);
#ifndef UIP_APPCALL
#define UIP_APPCALL web_appcall
#endif

void web_init(void);

#define fib_send(x, reg) do { uip_send(x, strlen(x)); fibre_yield(reg); } while(!uip_acked() || uip_rexmit())
#define fib_send_len(x, len, reg) do { uip_send(x, len); fibre_yield(reg); } while(!uip_acked() || uip_rexmit())

struct argData
{
	char *argName;
	char *argValue;
};

typedef int (*pageFunc)(struct argData *args, coStData *regs);

//This is for libhash
#define ptType pageFunc

#endif
