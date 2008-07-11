#ifndef CORODATAH
#define CORODATAH


#define setStack(sp) __asm__ \
	( \
		"movl %%eax, %%ebp\n" \
		"movl %%eax, %%esp\n" \
		\
		: \
		:"a"(sp) \
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


#endif
