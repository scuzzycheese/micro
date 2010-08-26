	.file	"test.c"
__SREG__ = 0x3f
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__CCP__  = 0x34
__tmp_reg__ = 0
__zero_reg__ = 1
	.global __do_copy_data
	.global __do_clear_bss
	.stabs	"/home/scuzzy/devel/test/avr/coro/",100,0,2,.Ltext0
	.stabs	"test.c",100,0,2,.Ltext0
	.text
.Ltext0:
	.stabs	"gcc2_compiled.",60,0,0,0
	.stabs	"int:t(0,1)=r(0,1);-32768;32767;",128,0,1,0
	.stabs	"char:t(0,2)=r(0,2);0;127;",128,0,1,0
	.stabs	"long int:t(0,3)=@s32;r(0,3);020000000000;017777777777;",128,0,1,0
	.stabs	"unsigned int:t(0,4)=r(0,4);0;0177777;",128,0,1,0
	.stabs	"long unsigned int:t(0,5)=@s32;r(0,5);0;037777777777;",128,0,1,0
	.stabs	"long long int:t(0,6)=@s64;r(0,6);01000000000000000000000;0777777777777777777777;",128,0,1,0
	.stabs	"long long unsigned int:t(0,7)=@s64;r(0,7);0;01777777777777777777777;",128,0,1,0
	.stabs	"short int:t(0,8)=r(0,8);-32768;32767;",128,0,1,0
	.stabs	"short unsigned int:t(0,9)=r(0,9);0;0177777;",128,0,1,0
	.stabs	"signed char:t(0,10)=@s8;r(0,10);-128;127;",128,0,1,0
	.stabs	"unsigned char:t(0,11)=@s8;r(0,11);0;255;",128,0,1,0
	.stabs	"float:t(0,12)=r(0,1);4;0;",128,0,1,0
	.stabs	"double:t(0,13)=r(0,1);4;0;",128,0,1,0
	.stabs	"long double:t(0,14)=r(0,1);4;0;",128,0,1,0
	.stabs	"void:t(0,15)=(0,15)",128,0,1,0
	.stabs	"/usr/lib/gcc/avr/4.3.2/../../../avr/include/stdio.h",130,0,0,0
	.stabs	"/usr/lib/gcc/avr/4.3.2/../../../avr/include/inttypes.h",130,0,0,0
	.stabs	"/usr/lib/gcc/avr/4.3.2/../../../avr/include/stdint.h",130,0,0,0
	.stabs	"int8_t:t(3,1)=(0,10)",128,0,121,0
	.stabs	"uint8_t:t(3,2)=(0,11)",128,0,122,0
	.stabs	"int16_t:t(3,3)=(0,1)",128,0,123,0
	.stabs	"uint16_t:t(3,4)=(0,4)",128,0,124,0
	.stabs	"int32_t:t(3,5)=(0,3)",128,0,125,0
	.stabs	"uint32_t:t(3,6)=(0,5)",128,0,126,0
	.stabs	"int64_t:t(3,7)=(0,6)",128,0,128,0
	.stabs	"uint64_t:t(3,8)=(0,7)",128,0,129,0
	.stabs	"intptr_t:t(3,9)=(3,3)",128,0,142,0
	.stabs	"uintptr_t:t(3,10)=(3,4)",128,0,147,0
	.stabs	"int_least8_t:t(3,11)=(3,1)",128,0,159,0
	.stabs	"uint_least8_t:t(3,12)=(3,2)",128,0,164,0
	.stabs	"int_least16_t:t(3,13)=(3,3)",128,0,169,0
	.stabs	"uint_least16_t:t(3,14)=(3,4)",128,0,174,0
	.stabs	"int_least32_t:t(3,15)=(3,5)",128,0,179,0
	.stabs	"uint_least32_t:t(3,16)=(3,6)",128,0,184,0
	.stabs	"int_least64_t:t(3,17)=(3,7)",128,0,192,0
	.stabs	"uint_least64_t:t(3,18)=(3,8)",128,0,199,0
	.stabs	"int_fast8_t:t(3,19)=(3,1)",128,0,213,0
	.stabs	"uint_fast8_t:t(3,20)=(3,2)",128,0,218,0
	.stabs	"int_fast16_t:t(3,21)=(3,3)",128,0,223,0
	.stabs	"uint_fast16_t:t(3,22)=(3,4)",128,0,228,0
	.stabs	"int_fast32_t:t(3,23)=(3,5)",128,0,233,0
	.stabs	"uint_fast32_t:t(3,24)=(3,6)",128,0,238,0
	.stabs	"int_fast64_t:t(3,25)=(3,7)",128,0,246,0
	.stabs	"uint_fast64_t:t(3,26)=(3,8)",128,0,253,0
	.stabs	"intmax_t:t(3,27)=(3,7)",128,0,273,0
	.stabs	"uintmax_t:t(3,28)=(3,8)",128,0,278,0
	.stabn	162,0,0,0
	.stabs	"int_farptr_t:t(2,1)=(3,5)",128,0,77,0
	.stabs	"uint_farptr_t:t(2,2)=(3,6)",128,0,81,0
	.stabn	162,0,0,0
	.stabs	"/usr/lib/gcc/avr/4.3.2/include/stdarg.h",130,0,0,0
	.stabs	"__gnuc_va_list:t(4,1)=(4,2)=*(0,15)",128,0,43,0
	.stabs	"va_list:t(4,3)=(4,1)",128,0,105,0
	.stabn	162,0,0,0
	.stabs	"/usr/lib/gcc/avr/4.3.2/include/stddef.h",130,0,0,0
	.stabs	"size_t:t(5,1)=(0,4)",128,0,214,0
	.stabn	162,0,0,0
	.stabs	"__file:T(1,1)=s14buf:(1,2)=*(0,2),0,16;unget:(0,11),16,8;flags:(3,2),24,8;size:(0,1),32,16;len:(0,1),48,16;put:(1,3)=*(1,4)=f(0,1),64,16;get:(1,5)=*(1,6)=f(0,1),80,16;udata:(1,7)=*(0,15),96,16;;",128,0,0,0
	.stabn	162,0,0,0
	.stabs	"/usr/lib/gcc/avr/4.3.2/../../../avr/include/stdlib.h",130,0,0,0
	.stabs	"/usr/lib/gcc/avr/4.3.2/include/stddef.h",130,0,0,0
	.stabs	"wchar_t:t(7,1)=(0,1)",128,0,326,0
	.stabn	162,0,0,0
	.stabs	"div_t:t(6,1)=(6,2)=s4quot:(0,1),0,16;rem:(0,1),16,16;;",128,0,71,0
	.stabs	"ldiv_t:t(6,3)=(6,4)=s8quot:(0,3),0,32;rem:(0,3),32,32;;",128,0,77,0
	.stabs	"__compar_fn_t:t(6,5)=(6,6)=*(6,7)=f(0,1)",128,0,80,0
	.stabn	162,0,0,0
	.stabs	"coroData.h",130,0,0,0
	.stabs	"fibreType:t(8,1)=(8,2)=*(8,3)=f(0,15)",128,0,10,0
	.stabs	"csd:T(8,4)=s15sp:(1,2),0,16;bp:(1,2),16,16;retAdd:(8,1),32,16;flags:(0,2),48,8;mallocStack:(1,2),56,16;next:(8,5)=*(8,4),72,16;prev:(8,5),88,16;last:(8,5),104,16;;",128,0,0,0
	.stabs	"coStData:t(8,6)=(8,4)",128,0,33,0
	.stabn	162,0,0,0
	.stabs	"fibre_yield:F(0,15)",36,0,9,fibre_yield
	.stabs	"rt:p(0,16)=*(8,6)",160,0,8,1
.global	fibre_yield
	.type	fibre_yield, @function
fibre_yield:
	.stabd	46,0,0
	.stabn	68,0,9,.LM0-.LFBB1
.LM0:
.LFBB1:
	push r29
	push r28
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 2 */
	std Y+2,r25
	std Y+1,r24
	.stabn	68,0,10,.LM1-.LFBB1
.LM1:
	ldd r30,Y+1
	ldd r31,Y+2
	ldd r24,Z+6
	ori r24,lo8(2)
	ldd r30,Y+1
	ldd r31,Y+2
	std Z+6,r24
	.stabn	68,0,11,.LM2-.LFBB1
.LM2:
	ldi r24,lo8(gs(.L2))
	ldi r25,hi8(gs(.L2))
	ldd r30,Y+1
	ldd r31,Y+2
	std Z+5,r25
	std Z+4,r24
.L2:
	.stabn	68,0,13,.LM3-.LFBB1
.LM3:
	ldd r30,Y+1
	ldd r31,Y+2
	ldd r24,Z+6
	clr r25
	sbrc r24,7
	com r25
	andi r24,lo8(2)
	andi r25,hi8(2)
	cp __zero_reg__,r24
	cpc __zero_reg__,r25
	brlt .+2
	rjmp .L4
	.stabn	68,0,19,.LM4-.LFBB1
.LM4:
	ldd r30,Y+1
	ldd r31,Y+2
/* #APP */
 ;  19 "test.c" 1
	push r0
push r1
push r2
push r3
push r4
push r5
push r6
push r7
push r8
push r9
push r10
push r11
push r12
push r13
push r14
push r15
push r16
push r17
push r18
push r19
push r20
push r21
push r22
push r23
push r24
push r25
push r26
push r27
push r28
push r29
push r30
push r31
in __tmp_reg__, __SP_L__
st Z+, __tmp_reg__
in __tmp_reg__, __SP_H__
st Z, __tmp_reg__
call MAINRET

 ;  0 "" 2
/* #NOAPP */
.L4:
/* epilogue start */
	.stabn	68,0,21,.LM5-.LFBB1
.LM5:
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	fibre_yield, .-fibre_yield
.Lscope1:
	.stabs	"",36,0,0,.Lscope1-.LFBB1
	.stabd	78,0,0
	.stabs	"blah:F(0,15)",36,0,24,blah
	.stabs	"rt:p(0,16)",160,0,23,3
.global	blah
	.type	blah, @function
blah:
	.stabd	46,0,0
	.stabn	68,0,24,.LM6-.LFBB2
.LM6:
.LFBB2:
	push r29
	push r28
	rcall .
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 4 */
	std Y+4,r25
	std Y+3,r24
	.stabn	68,0,25,.LM7-.LFBB2
.LM7:
	std Y+2,__zero_reg__
	std Y+1,__zero_reg__
	.stabn	68,0,29,.LM8-.LFBB2
.LM8:
	ldd r24,Y+1
	ldd r25,Y+2
	adiw r24,1
	std Y+2,r25
	std Y+1,r24
	.stabn	68,0,30,.LM9-.LFBB2
.LM9:
	ldd r24,Y+3
	ldd r25,Y+4
	rcall fibre_yield
	.stabn	68,0,33,.LM10-.LFBB2
.LM10:
	ldd r24,Y+1
	ldd r25,Y+2
	adiw r24,1
	std Y+2,r25
	std Y+1,r24
	.stabn	68,0,34,.LM11-.LFBB2
.LM11:
	ldd r24,Y+3
	ldd r25,Y+4
	rcall fibre_yield
	.stabn	68,0,37,.LM12-.LFBB2
.LM12:
	ldd r24,Y+1
	ldd r25,Y+2
	adiw r24,1
	std Y+2,r25
	std Y+1,r24
	.stabn	68,0,38,.LM13-.LFBB2
.LM13:
	ldd r24,Y+3
	ldd r25,Y+4
	rcall fibre_yield
/* epilogue start */
	.stabn	68,0,41,.LM14-.LFBB2
.LM14:
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	blah, .-blah
	.stabs	"count:(0,1)",128,0,25,1
	.stabn	192,0,0,.LFBB2-.LFBB2
	.stabn	224,0,0,.Lscope2-.LFBB2
.Lscope2:
	.stabs	"",36,0,0,.Lscope2-.LFBB2
	.stabd	78,0,0
	.stabs	"fibre_create:F(0,15)",36,0,45,fibre_create
	.stabs	"regs:p(0,16)",160,0,44,1
	.stabs	"rAdd:p(8,1)",160,0,44,3
	.stabs	"stackSize:p(0,1)",160,0,44,5
	.stabs	"stackPointer:p(1,2)",160,0,44,7
.global	fibre_create
	.type	fibre_create, @function
fibre_create:
	.stabd	46,0,0
	.stabn	68,0,45,.LM15-.LFBB3
.LM15:
.LFBB3:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
	sbiw r28,8
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
/* prologue: function */
/* frame size = 8 */
	std Y+2,r25
	std Y+1,r24
	std Y+4,r23
	std Y+3,r22
	std Y+6,r21
	std Y+5,r20
	std Y+8,r19
	std Y+7,r18
	.stabn	68,0,46,.LM16-.LFBB3
.LM16:
	ldd r30,Y+1
	ldd r31,Y+2
	ldd r24,Z+6
	andi r24,lo8(-3)
	ldd r30,Y+1
	ldd r31,Y+2
	std Z+6,r24
	.stabn	68,0,47,.LM17-.LFBB3
.LM17:
	ldd r30,Y+1
	ldd r31,Y+2
	ldd r24,Z+6
	andi r24,lo8(-2)
	ldd r30,Y+1
	ldd r31,Y+2
	std Z+6,r24
	.stabn	68,0,48,.LM18-.LFBB3
.LM18:
	ldd r30,Y+1
	ldd r31,Y+2
	ldd r24,Z+6
	andi r24,lo8(-9)
	ldd r30,Y+1
	ldd r31,Y+2
	std Z+6,r24
	.stabn	68,0,49,.LM19-.LFBB3
.LM19:
	ldd r30,Y+1
	ldd r31,Y+2
	ldd r24,Z+6
	ori r24,lo8(4)
	ldd r30,Y+1
	ldd r31,Y+2
	std Z+6,r24
	.stabn	68,0,51,.LM20-.LFBB3
.LM20:
	ldd r30,Y+1
	ldd r31,Y+2
	ldd r24,Y+3
	ldd r25,Y+4
	std Z+5,r25
	std Z+4,r24
	.stabn	68,0,52,.LM21-.LFBB3
.LM21:
	ldd r30,Y+1
	ldd r31,Y+2
	ldd r24,Y+7
	ldd r25,Y+8
	std Z+8,r25
	std Z+7,r24
	.stabn	68,0,53,.LM22-.LFBB3
.LM22:
	ldd r30,Y+1
	ldd r31,Y+2
	ldd r18,Z+7
	ldd r19,Z+8
	ldd r24,Y+5
	ldd r25,Y+6
	sbiw r24,1
	add r24,r18
	adc r25,r19
	ldd r30,Y+1
	ldd r31,Y+2
	std Z+1,r25
	st Z,r24
	.stabn	68,0,55,.LM23-.LFBB3
.LM23:
	lds r24,mainRegs+9
	lds r25,(mainRegs+9)+1
	sbiw r24,0
	brne .L8
	.stabn	68,0,57,.LM24-.LFBB3
.LM24:
	ldd r24,Y+1
	ldd r25,Y+2
	sts (mainRegs+9)+1,r25
	sts mainRegs+9,r24
	.stabn	68,0,58,.LM25-.LFBB3
.LM25:
	ldd r24,Y+1
	ldd r25,Y+2
	sts (mainRegs+13)+1,r25
	sts mainRegs+13,r24
	.stabn	68,0,59,.LM26-.LFBB3
.LM26:
	ldd r30,Y+1
	ldd r31,Y+2
	ldd r24,Y+1
	ldd r25,Y+2
	std Z+10,r25
	std Z+9,r24
	.stabn	68,0,60,.LM27-.LFBB3
.LM27:
	ldd r30,Y+1
	ldd r31,Y+2
	ldd r24,Y+1
	ldd r25,Y+2
	std Z+12,r25
	std Z+11,r24
	rjmp .L10
.L8:
	.stabn	68,0,64,.LM28-.LFBB3
.LM28:
	lds r30,mainRegs+13
	lds r31,(mainRegs+13)+1
	ldd r24,Y+1
	ldd r25,Y+2
	std Z+10,r25
	std Z+9,r24
	.stabn	68,0,65,.LM29-.LFBB3
.LM29:
	lds r24,mainRegs+13
	lds r25,(mainRegs+13)+1
	ldd r30,Y+1
	ldd r31,Y+2
	std Z+12,r25
	std Z+11,r24
	.stabn	68,0,66,.LM30-.LFBB3
.LM30:
	ldd r24,Y+1
	ldd r25,Y+2
	sts (mainRegs+13)+1,r25
	sts mainRegs+13,r24
	.stabn	68,0,67,.LM31-.LFBB3
.LM31:
	lds r24,mainRegs+9
	lds r25,(mainRegs+9)+1
	ldd r30,Y+1
	ldd r31,Y+2
	std Z+10,r25
	std Z+9,r24
	.stabn	68,0,69,.LM32-.LFBB3
.LM32:
	lds r30,mainRegs+9
	lds r31,(mainRegs+9)+1
	lds r24,mainRegs+13
	lds r25,(mainRegs+13)+1
	std Z+12,r25
	std Z+11,r24
.L10:
/* epilogue start */
	.stabn	68,0,71,.LM33-.LFBB3
.LM33:
	adiw r28,8
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
	pop r28
	pop r29
	ret
	.size	fibre_create, .-fibre_create
.Lscope3:
	.stabs	"",36,0,0,.Lscope3-.LFBB3
	.stabd	78,0,0
	.stabs	"fibres_start:F(0,15)",36,0,74,fibres_start
.global	fibres_start
	.type	fibres_start, @function
fibres_start:
	.stabd	46,0,0
	.stabn	68,0,74,.LM34-.LFBB4
.LM34:
.LFBB4:
	push r29
	push r28
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 2 */
	.stabn	68,0,75,.LM35-.LFBB4
.LM35:
	lds r24,mainRegs+9
	lds r25,(mainRegs+9)+1
	std Y+2,r25
	std Y+1,r24
	rjmp .L12
.L17:
	.stabn	68,0,82,.LM36-.LFBB4
.LM36:
	ldd r30,Y+1
	ldd r31,Y+2
	ldd r24,Z+6
	andi r24,lo8(-3)
	ldd r30,Y+1
	ldd r31,Y+2
	std Z+6,r24
	.stabn	68,0,87,.LM37-.LFBB4
.LM37:
	ldi r30,lo8(mainRegs)
	ldi r31,hi8(mainRegs)
/* #APP */
 ;  87 "test.c" 1
	push r0
push r1
push r2
push r3
push r4
push r5
push r6
push r7
push r8
push r9
push r10
push r11
push r12
push r13
push r14
push r15
push r16
push r17
push r18
push r19
push r20
push r21
push r22
push r23
push r24
push r25
push r26
push r27
push r28
push r29
push r30
push r31
in __tmp_reg__, __SP_L__
st Z+, __tmp_reg__
in __tmp_reg__, __SP_H__
st Z, __tmp_reg__

 ;  0 "" 2
	.stabn	68,0,90,.LM38-.LFBB4
.LM38:
 ;  90 "test.c" 1
	MAINRET:
 ;  0 "" 2
	.stabn	68,0,91,.LM39-.LFBB4
.LM39:
/* #NOAPP */
	ldi r30,lo8(mainRegs)
	ldi r31,hi8(mainRegs)
/* #APP */
 ;  91 "test.c" 1
	ld __tmp_reg__, Z+
out __SP_L__, __tmp_reg__
ld __tmp_reg__, Z+
out __SP_H__, __tmp_reg__
pop r0
pop r1
pop r2
pop r3
pop r4
pop r5
pop r6
pop r7
pop r8
pop r9
pop r10
pop r11
pop r12
pop r13
pop r14
pop r15
pop r16
pop r17
pop r18
pop r19
pop r20
pop r21
pop r22
pop r23
pop r24
pop r25
pop r26
pop r27
pop r28
pop r29
pop r30
pop r31

 ;  0 "" 2
	.stabn	68,0,94,.LM40-.LFBB4
.LM40:
/* #NOAPP */
	ldd r30,Y+1
	ldd r31,Y+2
	ldd r24,Z+6
	clr r25
	sbrc r24,7
	com r25
	andi r24,lo8(2)
	andi r25,hi8(2)
	cp __zero_reg__,r24
	cpc __zero_reg__,r25
	brge .+2
	rjmp .L13
	ldd r30,Y+1
	ldd r31,Y+2
	ldd r24,Z+6
	clr r25
	sbrc r24,7
	com r25
	andi r24,lo8(8)
	andi r25,hi8(8)
	cp __zero_reg__,r24
	cpc __zero_reg__,r25
	brge .+2
	rjmp .L13
	ldd r30,Y+1
	ldd r31,Y+2
	ldd r24,Z+6
	clr r25
	sbrc r24,7
	com r25
	andi r24,lo8(4)
	andi r25,hi8(4)
	cp __zero_reg__,r24
	cpc __zero_reg__,r25
	brlt .+2
	rjmp .L13
	.stabn	68,0,96,.LM41-.LFBB4
.LM41:
	ldd r30,Y+1
	ldd r31,Y+2
	ldd r24,Z+6
	clr r25
	sbrc r24,7
	com r25
	andi r24,lo8(1)
	andi r25,hi8(1)
	cp __zero_reg__,r24
	cpc __zero_reg__,r25
	brge .+2
	rjmp .L14
	.stabn	68,0,100,.LM42-.LFBB4
.LM42:
	ldd r30,Y+1
	ldd r31,Y+2
	ldd r24,Z+6
	ori r24,lo8(1)
	ldd r30,Y+1
	ldd r31,Y+2
	std Z+6,r24
	.stabn	68,0,104,.LM43-.LFBB4
.LM43:
	ldd r30,Y+1
	ldd r31,Y+2
	ld r24,Z
	ldd r25,Z+1
	sbiw r24,2
	ldd r30,Y+1
	ldd r31,Y+2
	std Z+1,r25
	st Z,r24
	.stabn	68,0,107,.LM44-.LFBB4
.LM44:
	ldd r30,Y+1
	ldd r31,Y+2
	ld r24,Z
	ldd r25,Z+1
	movw r30,r24
	ldd r24,Y+1
	ldd r25,Y+2
	std Z+1,r25
	st Z,r24
	.stabn	68,0,110,.LM45-.LFBB4
.LM45:
	ldd r30,Y+1
	ldd r31,Y+2
	ld r26,Z
	ldd r27,Z+1
	ldd r30,Y+1
	ldd r31,Y+2
	ldd __tmp_reg__,Z+4
	ldd r31,Z+5
	mov r30,__tmp_reg__
/* #APP */
 ;  110 "test.c" 1
	out __SP_H__, r27
out __SP_L__, r26
in r29, __SP_H__
in r28, __SP_L__
icall

 ;  0 "" 2
	.stabn	68,0,112,.LM46-.LFBB4
.LM46:
/* #NOAPP */
	ldi r30,lo8(mainRegs)
	ldi r31,hi8(mainRegs)
/* #APP */
 ;  112 "test.c" 1
	ld __tmp_reg__, Z+
out __SP_L__, __tmp_reg__
ld __tmp_reg__, Z+
out __SP_H__, __tmp_reg__
pop r0
pop r1
pop r2
pop r3
pop r4
pop r5
pop r6
pop r7
pop r8
pop r9
pop r10
pop r11
pop r12
pop r13
pop r14
pop r15
pop r16
pop r17
pop r18
pop r19
pop r20
pop r21
pop r22
pop r23
pop r24
pop r25
pop r26
pop r27
pop r28
pop r29
pop r30
pop r31

 ;  0 "" 2
	.stabn	68,0,114,.LM47-.LFBB4
.LM47:
/* #NOAPP */
	ldd r30,Y+1
	ldd r31,Y+2
	ldd r24,Z+6
	ori r24,lo8(8)
	ldd r30,Y+1
	ldd r31,Y+2
	std Z+6,r24
	rjmp .L13
.L14:
	.stabn	68,0,119,.LM48-.LFBB4
.LM48:
	ldd r30,Y+1
	ldd r31,Y+2
/* #APP */
 ;  119 "test.c" 1
	ld __tmp_reg__, Z+
out __SP_L__, __tmp_reg__
ld __tmp_reg__, Z+
out __SP_H__, __tmp_reg__
ld __tmp_reg__, Z+
ld __tmp_reg__, Z+
pop r0
pop r1
pop r2
pop r3
pop r4
pop r5
pop r6
pop r7
pop r8
pop r9
pop r10
pop r11
pop r12
pop r13
pop r14
pop r15
pop r16
pop r17
pop r18
pop r19
pop r20
pop r21
pop r22
pop r23
pop r24
pop r25
pop r26
pop r27
pop r28
pop r29
pop r30
pop r31
ijmp

 ;  0 "" 2
/* #NOAPP */
.L13:
	.stabn	68,0,122,.LM49-.LFBB4
.LM49:
	ldd r30,Y+1
	ldd r31,Y+2
	ldd r24,Z+6
	clr r25
	sbrc r24,7
	com r25
	andi r24,lo8(8)
	andi r25,hi8(8)
	cp __zero_reg__,r24
	cpc __zero_reg__,r25
	brge .L15
	ldd r30,Y+1
	ldd r31,Y+2
	ldd r24,Z+7
	ldd r25,Z+8
	sbiw r24,0
	breq .L15
	.stabn	68,0,124,.LM50-.LFBB4
.LM50:
	ldd r30,Y+1
	ldd r31,Y+2
	ldd __tmp_reg__,Z+11
	ldd r31,Z+12
	mov r30,__tmp_reg__
	ldd r18,Z+9
	ldd r19,Z+10
	ldd r30,Y+1
	ldd r31,Y+2
	ldd r24,Z+9
	ldd r25,Z+10
	cp r18,r24
	cpc r19,r25
	brne .L16
	.stabn	68,0,126,.LM51-.LFBB4
.LM51:
	sts (mainRegs+9)+1,__zero_reg__
	sts mainRegs+9,__zero_reg__
	rjmp .L15
.L16:
	.stabn	68,0,130,.LM52-.LFBB4
.LM52:
	ldd r30,Y+1
	ldd r31,Y+2
	ldd r26,Z+11
	ldd r27,Z+12
	ldd r30,Y+1
	ldd r31,Y+2
	ldd r24,Z+9
	ldd r25,Z+10
	adiw r26,9+1
	st X,r25
	st -X,r24
	sbiw r26,9
.L15:
	.stabn	68,0,133,.LM53-.LFBB4
.LM53:
	ldd r30,Y+1
	ldd r31,Y+2
	ldd r24,Z+9
	ldd r25,Z+10
	std Y+2,r25
	std Y+1,r24
.L12:
	.stabn	68,0,79,.LM54-.LFBB4
.LM54:
	lds r24,mainRegs+9
	lds r25,(mainRegs+9)+1
	sbiw r24,0
	breq .+2
	rjmp .L17
/* epilogue start */
	.stabn	68,0,136,.LM55-.LFBB4
.LM55:
	pop __tmp_reg__
	pop __tmp_reg__
	pop r28
	pop r29
	ret
	.size	fibres_start, .-fibres_start
	.stabs	"curCoRo:(0,16)",128,0,75,1
	.stabn	192,0,0,.LFBB4-.LFBB4
	.stabn	224,0,0,.Lscope4-.LFBB4
.Lscope4:
	.stabs	"",36,0,0,.Lscope4-.LFBB4
	.stabd	78,0,0
	.stabs	"main:F(0,1)",36,0,140,main
	.stabs	"argc:p(0,1)",160,0,139,346
	.stabs	"argv:p(0,17)=*(1,2)",160,0,139,348
.global	main
	.type	main, @function
main:
	.stabd	46,0,0
	.stabn	68,0,140,.LM56-.LFBB5
.LM56:
.LFBB5:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
	subi r28,lo8(-(-349))
	sbci r29,hi8(-(-349))
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
/* prologue: function */
/* frame size = 349 */
	movw r30,r28
	subi r30,lo8(-(346))
	sbci r31,hi8(-(346))
	std Z+1,r25
	st Z,r24
	movw r30,r28
	subi r30,lo8(-(348))
	sbci r31,hi8(-(348))
	std Z+1,r23
	st Z,r22
	.stabn	68,0,147,.LM57-.LFBB5
.LM57:
	movw r30,r28
	adiw r30,46
	ldi r18,lo8(gs(blah))
	ldi r19,hi8(gs(blah))
	movw r24,r28
	adiw r24,1
	movw r22,r18
	ldi r20,lo8(100)
	ldi r21,hi8(100)
	movw r18,r30
	rcall fibre_create
	.stabn	68,0,148,.LM58-.LFBB5
.LM58:
	movw r24,r28
	adiw r24,46
	movw r30,r24
	subi r30,lo8(-(100))
	sbci r31,hi8(-(100))
	movw r24,r28
	adiw r24,16
	ldi r18,lo8(gs(blah))
	ldi r19,hi8(gs(blah))
	movw r22,r18
	ldi r20,lo8(100)
	ldi r21,hi8(100)
	movw r18,r30
	rcall fibre_create
	.stabn	68,0,149,.LM59-.LFBB5
.LM59:
	movw r24,r28
	adiw r24,46
	movw r30,r24
	subi r30,lo8(-(200))
	sbci r31,hi8(-(200))
	movw r24,r28
	adiw r24,31
	ldi r18,lo8(gs(blah))
	ldi r19,hi8(gs(blah))
	movw r22,r18
	ldi r20,lo8(100)
	ldi r21,hi8(100)
	movw r18,r30
	rcall fibre_create
	.stabn	68,0,152,.LM60-.LFBB5
.LM60:
	rcall fibres_start
	.stabn	68,0,156,.LM61-.LFBB5
.LM61:
	ldi r24,lo8(0)
	ldi r25,hi8(0)
/* epilogue start */
	.stabn	68,0,157,.LM62-.LFBB5
.LM62:
	subi r28,lo8(-(349))
	sbci r29,hi8(-(349))
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
	pop r28
	pop r29
	ret
	.size	main, .-main
	.stabs	"routineRegs:(0,18)=ar(0,19)=r(0,19);0;0177777;;0;2;(8,6)",128,0,143,1
	.stabs	"stack:(0,20)=ar(0,19);0;2;(0,21)=ar(0,19);0;99;(0,2)",128,0,144,46
	.stabn	192,0,0,.LFBB5-.LFBB5
	.stabn	224,0,0,.Lscope5-.LFBB5
.Lscope5:
	.stabs	"",36,0,0,.Lscope5-.LFBB5
	.stabd	78,0,0
	.lcomm mainRegs,15
	.stabs	"mainRegs:S(0,22)=B(8,6)",40,0,5,mainRegs
	.stabs	"",100,0,0,.Letext0
.Letext0:
