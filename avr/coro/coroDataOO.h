#ifndef CORODATAOOH
#define CORODATAOOH

//Some lovely foward declairation
struct csd;

typedef void (*fibreType)(struct csd *);

//NOTE: this is packed, to make it as small as possible
struct csd 
{
	//the following 7 members have to be in this exact order
	//at the top of this struct
	int ebx;
	int esi;
	int edi;
	int esp;
	int ecx;
	int ebp;
	fibreType retAdd;

	//These flags contain statuses about the fibre
	char flags;

	char *SP;
	char *mallocStack;
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
#define setStackAndCallToAdd(sp,add) __asm__ \
( \
	"movl %%eax, %%ebp\n" \
	"movl %%eax, %%esp\n" \
	"call *%%ebx\n" \
	\
	: \
	:"a"(sp),"b"(add) \
)

#define setStack(sp) __asm__ \
( \
	"movl %%eax, %%ebp\n" \
	"movl %%eax, %%esp\n" \
	\
	: \
	:"a"(sp) \
)

#define callToAdd(add) __asm__ \
( \
	"call *%%eax" \
	\
	: \
	:"a"(add) \
)

#define jmpToAdd(add) __asm__ \
( \
	"jmp *%%eax" \
	\
	: \
	:"a"(add) \
)

//I don't know, but I might have to push a random value onto the stack
//so it's taken off when we return to this address of execution, but
//this will result in EAX being trashed
//This would be so much easier if I just had access to the current
//execution address(thanks intel)
#define getExecAdd(add) __asm__ __volatile__ \
( \
	"call getEIP%=\n" \
	"pushl $0\n" \
	"getEIP%=:\n" \
	"popl %%eax" \
	\
	:"=a"(add) \
	: \
)

#define regSave(buf) __asm__ \
( \
	"movl %%ebx, (%%eax)\n" \
	"movl %%esi, (4)(%%eax)\n" \
	"movl %%edi, (8)(%%eax)\n" \
	"movl %%esp, (12)(%%eax)\n" \
	"movl %%ecx, (16)(%%eax)\n" \
	"movl %%ebp, (20)(%%eax)\n" \
	\
	: \
	:"a"(buf) \
)


#define regRestore(buf) __asm__ \
( \
	"movl (%%eax), %%ebx\n" \
	"movl (4)(%%eax), %%esi\n" \
	"movl (8)(%%eax), %%edi\n" \
	"movl (12)(%%eax), %%esp\n" \
	"movl (16)(%%eax), %%ecx\n" \
	"movl (20)(%%eax), %%ebp\n" \
	\
	: \
	:"a"(buf) \
)


#define regRestoreAndJmpToAdd(buf) __asm__ \
( \
	"movl (%%eax), %%ebx\n" \
	"movl (4)(%%eax), %%esi\n" \
	"movl (8)(%%eax), %%edi\n" \
	"movl (12)(%%eax), %%esp\n" \
	"movl (16)(%%eax), %%ecx\n" \
	"movl (20)(%%eax), %%ebp\n" \
	"jmp *(24)(%%eax)" \
	\
	: \
	:"a"(buf) \
)


#endif
