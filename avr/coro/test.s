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
	.stabs	"/usr/lib/gcc/avr/4.3.2/../../../avr/include/avr/io.h",130,0,0,0
	.stabs	"/usr/lib/gcc/avr/4.3.2/../../../avr/include/avr/fuse.h",130,0,0,0
	.stabs	"__fuse_t:t(10,1)=(10,2)=s2low:(0,11),0,8;high:(0,11),8,8;;",128,0,227,0
	.stabn	162,0,0,0
	.stabn	162,0,0,0
	.stabs	"fibreType:t(8,1)=(8,2)=*(8,3)=f(0,15)",128,0,10,0
	.stabs	"csd:T(8,4)=s47r0:(3,2),0,8;r1:(3,2),8,8;r2:(3,2),16,8;r3:(3,2),24,8;r4:(3,2),32,8;r5:(3,2),40,8;r6:(3,2),48,8;r7:(3,2),56,8;r8:(3,2),64,8;r9:(3,2),72,8;r10:(3,2),80,8;r11:(3,2),88,8;r12:(3,2),96,8;r13:(3,2),104,8;r14:(3,2),112,8;r15:(3,2),120,8;r16:(3,2),128,8;r17:(3,2),136,8;r18:(3,2),144,8;r19:(3,2),152,8;r20:(3,2),160,8;r21:(3,2),168,8;r22:(3,2),176,8;r23:(3,2),184,8;r24:(3,2),192,8;r25:(3,2),200,8;r26:(3,2),208,8;r27:(3,2),216,8;r28:(3,2),224,8;r29:(3,2),232,8;r30:(3,2),240,8;r31:(3,2),248,8;sp:(1,2),256,16;bp:(1,2),272,16;retAdd:(1,7),288,16;flags:(0,2),304,8;mallocStack:(1,2),312,16;next:(8,5)=*(8,4),328,16;prev:(8,5),344,16;last:(8,5),360,16;;",128,0,0,0
	.stabs	"coStData:t(8,6)=(8,4)",128,0,65,0
	.stabn	162,0,0,0
	.stabs	"fibre_yield:F(0,15)",36,0,9,fibre_yield
	.stabs	"rt:P(0,16)=*(8,6)",64,0,8,30
.global	fibre_yield
	.type	fibre_yield, @function
fibre_yield:
	.stabd	46,0,0
	.stabn	68,0,9,.LM0-.LFBB1
.LM0:
.LFBB1:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
	movw r30,r24
	.stabn	68,0,10,.LM1-.LFBB1
.LM1:
	ldd r18,Z+38
	ori r18,lo8(2)
	std Z+38,r18
	.stabn	68,0,11,.LM2-.LFBB1
.LM2:
	ldi r24,lo8(gs(.L2))
	ldi r25,hi8(gs(.L2))
	std Z+37,r25
	std Z+36,r24
.L2:
	.stabn	68,0,13,.LM3-.LFBB1
.LM3:
	sbrs r18,1
	rjmp .L4
	.stabn	68,0,17,.LM4-.LFBB1
.LM4:
/* #APP */
 ;  17 "test.c" 1
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
in __tmp_reg__, __SP_H__
st Z+, __tmp_reg__
in __tmp_reg__, __SP_L__
st Z+, __tmp_reg__
st Z+, r29
st Z, r28

 ;  0 "" 2
	.stabn	68,0,18,.LM5-.LFBB1
.LM5:
/* #NOAPP */
	lds r30,mainRegs+36
	lds r31,(mainRegs+36)+1
/* #APP */
 ;  18 "test.c" 1
	ijmp
 ;  0 "" 2
/* #NOAPP */
.L4:
/* epilogue start */
	.stabn	68,0,20,.LM6-.LFBB1
.LM6:
	pop r28
	pop r29
	ret
	.size	fibre_yield, .-fibre_yield
.Lscope1:
	.stabs	"",36,0,0,.Lscope1-.LFBB1
	.stabd	78,0,0
	.stabs	"fibre_create:F(0,15)",36,0,44,fibre_create
	.stabs	"regs:P(0,16)",64,0,43,26
	.stabs	"rAdd:P(8,1)",64,0,43,22
	.stabs	"stackSize:P(0,1)",64,0,43,20
	.stabs	"stackPointer:P(1,2)",64,0,43,18
.global	fibre_create
	.type	fibre_create, @function
fibre_create:
	.stabd	46,0,0
	.stabn	68,0,44,.LM7-.LFBB2
.LM7:
.LFBB2:
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
	movw r26,r24
	.stabn	68,0,48,.LM8-.LFBB2
.LM8:
	adiw r26,38
	ld r24,X
	sbiw r26,38
	andi r24,lo8(-12)
	ori r24,lo8(4)
	adiw r26,38
	st X,r24
	sbiw r26,38
	.stabn	68,0,50,.LM9-.LFBB2
.LM9:
	adiw r26,36+1
	st X,r23
	st -X,r22
	sbiw r26,36
	.stabn	68,0,51,.LM10-.LFBB2
.LM10:
	adiw r26,39+1
	st X,r19
	st -X,r18
	sbiw r26,39
	.stabn	68,0,52,.LM11-.LFBB2
.LM11:
	subi r20,lo8(-(-1))
	sbci r21,hi8(-(-1))
	add r18,r20
	adc r19,r21
	adiw r26,32+1
	st X,r19
	st -X,r18
	sbiw r26,32
	.stabn	68,0,54,.LM12-.LFBB2
.LM12:
	lds r24,mainRegs+41
	lds r25,(mainRegs+41)+1
	or r24,r25
	brne .L6
	.stabn	68,0,56,.LM13-.LFBB2
.LM13:
	sts (mainRegs+41)+1,r27
	sts mainRegs+41,r26
	.stabn	68,0,57,.LM14-.LFBB2
.LM14:
	sts (mainRegs+45)+1,r27
	sts mainRegs+45,r26
	.stabn	68,0,58,.LM15-.LFBB2
.LM15:
	mov __tmp_reg__,r26
	mov __zero_reg__,r27
	adiw r26,41+1
	st X,__zero_reg__
	st -X,__tmp_reg__
	clr __zero_reg__
	sbiw r26,41
	.stabn	68,0,59,.LM16-.LFBB2
.LM16:
	mov __tmp_reg__,r26
	mov __zero_reg__,r27
	adiw r26,43+1
	st X,__zero_reg__
	st -X,__tmp_reg__
	clr __zero_reg__
	sbiw r26,43
	rjmp .L8
.L6:
	.stabn	68,0,63,.LM17-.LFBB2
.LM17:
	lds r30,mainRegs+45
	lds r31,(mainRegs+45)+1
	std Z+42,r27
	std Z+41,r26
	.stabn	68,0,64,.LM18-.LFBB2
.LM18:
	lds r24,mainRegs+45
	lds r25,(mainRegs+45)+1
	adiw r26,43+1
	st X,r25
	st -X,r24
	sbiw r26,43
	.stabn	68,0,65,.LM19-.LFBB2
.LM19:
	sts (mainRegs+45)+1,r27
	sts mainRegs+45,r26
	.stabn	68,0,66,.LM20-.LFBB2
.LM20:
	lds r24,mainRegs+41
	lds r25,(mainRegs+41)+1
	adiw r26,41+1
	st X,r25
	st -X,r24
	sbiw r26,41
	.stabn	68,0,68,.LM21-.LFBB2
.LM21:
	lds r30,mainRegs+41
	lds r31,(mainRegs+41)+1
	lds r24,mainRegs+45
	lds r25,(mainRegs+45)+1
	std Z+44,r25
	std Z+43,r24
.L8:
/* epilogue start */
	.stabn	68,0,70,.LM22-.LFBB2
.LM22:
	pop r28
	pop r29
	ret
	.size	fibre_create, .-fibre_create
.Lscope2:
	.stabs	"",36,0,0,.Lscope2-.LFBB2
	.stabd	78,0,0
	.data
.LC0:
	.string	"Begin loop"
.LC1:
	.string	"End loop"
	.text
	.stabs	"fibres_start:F(0,15)",36,0,73,fibres_start
.global	fibres_start
	.type	fibres_start, @function
fibres_start:
	.stabd	46,0,0
	.stabn	68,0,73,.LM23-.LFBB3
.LM23:
.LFBB3:
	push r12
	push r13
	push r14
	push r15
	push r16
	push r17
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
	.stabn	68,0,74,.LM24-.LFBB3
.LM24:
	lds r16,mainRegs+41
	lds r17,(mainRegs+41)+1
	.stabn	68,0,86,.LM25-.LFBB3
.LM25:
	ldi r25,lo8(mainRegs)
	mov r14,r25
	ldi r25,hi8(mainRegs)
	mov r15,r25
	.stabn	68,0,87,.LM26-.LFBB3
.LM26:
	ldi r24,lo8(gs(.L11))
	mov r12,r24
	ldi r24,hi8(gs(.L11))
	mov r13,r24
	rjmp .L10
.L16:
	.stabn	68,0,80,.LM27-.LFBB3
.LM27:
	ldi r24,lo8(.LC0)
	ldi r25,hi8(.LC0)
	rcall puts
	.stabn	68,0,81,.LM28-.LFBB3
.LM28:
	movw r26,r16
	adiw r26,38
	ld r24,X
	sbiw r26,38
	andi r24,lo8(-3)
	adiw r26,38
	st X,r24
	.stabn	68,0,86,.LM29-.LFBB3
.LM29:
	movw r30,r14
/* #APP */
 ;  86 "test.c" 1
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
in __tmp_reg__, __SP_H__
st Z+, __tmp_reg__
in __tmp_reg__, __SP_L__
st Z+, __tmp_reg__
st Z+, r29
st Z, r28

 ;  0 "" 2
	.stabn	68,0,87,.LM30-.LFBB3
.LM30:
/* #NOAPP */
	sts (mainRegs+36)+1,r13
	sts mainRegs+36,r12
.L11:
	.stabn	68,0,89,.LM31-.LFBB3
.LM31:
	movw r26,r14
/* #APP */
 ;  89 "test.c" 1
	ld __tmp_reg__, X+
out __SP_H__, __tmp_reg__
ld __tmp_reg__, X+
out __SP_L__, __tmp_reg__
ld r29, X+
ld r28, X
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
	.stabn	68,0,92,.LM32-.LFBB3
.LM32:
/* #NOAPP */
	movw r30,r16
	ldd r18,Z+38
	mov r24,r18
	clr r25
	sbrc r24,7
	com r25
	sbrc r24,1
	rjmp .L12
	sbrc r24,3
	rjmp .L12
	sbrs r24,2
	rjmp .L12
	.stabn	68,0,94,.LM33-.LFBB3
.LM33:
	sbrc r24,0
	rjmp .L13
	.stabn	68,0,98,.LM34-.LFBB3
.LM34:
	ori r18,lo8(1)
	std Z+38,r18
	.stabn	68,0,102,.LM35-.LFBB3
.LM35:
	ldd r18,Z+32
	ldd r19,Z+33
	subi r18,lo8(-(-2))
	sbci r19,hi8(-(-2))
	std Z+33,r19
	std Z+32,r18
	.stabn	68,0,105,.LM36-.LFBB3
.LM36:
	movw r26,r18
	adiw r26,1
	st X,r17
	st -X,r16
	.stabn	68,0,108,.LM37-.LFBB3
.LM37:
	ldd r24,Z+36
	ldd r25,Z+37
	movw r30,r24
/* #APP */
 ;  108 "test.c" 1
	ld __tmp_reg__, X+
out __SP_H__, __tmp_reg__
ld __tmp_reg__, X+
out __SP_L__, __tmp_reg__
in r29, __SP_H__
in r28, __SP_L__
icall

 ;  0 "" 2
	.stabn	68,0,110,.LM38-.LFBB3
.LM38:
/* #NOAPP */
	movw r26,r14
/* #APP */
 ;  110 "test.c" 1
	ld __tmp_reg__, X+
out __SP_H__, __tmp_reg__
ld __tmp_reg__, X+
out __SP_L__, __tmp_reg__
ld r29, X+
ld r28, X
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
	.stabn	68,0,112,.LM39-.LFBB3
.LM39:
/* #NOAPP */
	movw r30,r16
	ldd r24,Z+38
	ori r24,lo8(8)
	std Z+38,r24
	rjmp .L12
.L13:
	.stabn	68,0,117,.LM40-.LFBB3
.LM40:
	movw r26,r16
/* #APP */
 ;  117 "test.c" 1
	ld __tmp_reg__, X+
out __SP_H__, __tmp_reg__
ld __tmp_reg__, X+
out __SP_L__, __tmp_reg__
ld r29, X+
ld r28, X+
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
.L12:
	.stabn	68,0,120,.LM41-.LFBB3
.LM41:
	movw r30,r16
	ldd r24,Z+38
	sbrs r24,3
	rjmp .L14
	ldd r24,Z+39
	ldd r25,Z+40
	or r24,r25
	breq .L14
	.stabn	68,0,122,.LM42-.LFBB3
.LM42:
	ldd __tmp_reg__,Z+43
	ldd r31,Z+44
	mov r30,__tmp_reg__
	movw r26,r16
	adiw r26,41
	ld r18,X+
	ld r19,X
	sbiw r26,41+1
	ldd r24,Z+41
	ldd r25,Z+42
	cp r24,r18
	cpc r25,r19
	brne .L15
	.stabn	68,0,124,.LM43-.LFBB3
.LM43:
	sts (mainRegs+41)+1,__zero_reg__
	sts mainRegs+41,__zero_reg__
	rjmp .L14
.L15:
	.stabn	68,0,128,.LM44-.LFBB3
.LM44:
	std Z+42,r19
	std Z+41,r18
.L14:
	.stabn	68,0,131,.LM45-.LFBB3
.LM45:
	movw r30,r16
	ldd r16,Z+41
	ldd r17,Z+42
	.stabn	68,0,132,.LM46-.LFBB3
.LM46:
	ldi r24,lo8(.LC1)
	ldi r25,hi8(.LC1)
	rcall puts
.L10:
	.stabn	68,0,78,.LM47-.LFBB3
.LM47:
	lds r24,mainRegs+41
	lds r25,(mainRegs+41)+1
	or r24,r25
	breq .+2
	rjmp .L16
/* epilogue start */
	.stabn	68,0,134,.LM48-.LFBB3
.LM48:
	pop r28
	pop r29
	pop r17
	pop r16
	pop r15
	pop r14
	pop r13
	pop r12
	ret
	.size	fibres_start, .-fibres_start
	.stabs	"curCoRo:r(0,16)",64,0,74,16
	.stabn	192,0,0,.LFBB3-.LFBB3
	.stabn	224,0,0,.Lscope3-.LFBB3
.Lscope3:
	.stabs	"",36,0,0,.Lscope3-.LFBB3
	.stabd	78,0,0
	.data
.LC2:
	.string	"Co-Routine storage size: %d\n"
.LC3:
	.string	"Fibres finished"
	.text
	.stabs	"main:F(0,1)",36,0,138,main
	.stabs	"argc:P(0,1)",64,0,137,24
	.stabs	"argv:P(0,17)=*(1,2)",64,0,137,22
.global	main
	.type	main, @function
main:
	.stabd	46,0,0
	.stabn	68,0,138,.LM49-.LFBB4
.LM49:
.LFBB4:
	push r16
	push r17
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
	subi r28,lo8(-(-30141))
	sbci r29,hi8(-(-30141))
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
/* prologue: function */
/* frame size = 30141 */
	.stabn	68,0,139,.LM50-.LFBB4
.LM50:
	rcall .
	rcall .
	ldi r24,lo8(.LC2)
	ldi r25,hi8(.LC2)
	in r30,__SP_L__
	in r31,__SP_H__
	std Z+2,r25
	std Z+1,r24
	ldi r24,lo8(47)
	ldi r25,hi8(47)
	std Z+4,r25
	std Z+3,r24
	rcall printf
	.stabn	68,0,145,.LM51-.LFBB4
.LM51:
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	ldi r16,lo8(gs(blah))
	ldi r17,hi8(gs(blah))
	movw r24,r28
	adiw r24,1
	movw r22,r16
	ldi r20,lo8(10000)
	ldi r21,hi8(10000)
	movw r18,r28
	subi r18,lo8(-(142))
	sbci r19,hi8(-(142))
	rcall fibre_create
	.stabn	68,0,146,.LM52-.LFBB4
.LM52:
	movw r24,r28
	adiw r24,48
	movw r22,r16
	ldi r20,lo8(10000)
	ldi r21,hi8(10000)
	movw r18,r28
	subi r18,lo8(-(10142))
	sbci r19,hi8(-(10142))
	rcall fibre_create
	.stabn	68,0,147,.LM53-.LFBB4
.LM53:
	movw r24,r28
	subi r24,lo8(-(95))
	sbci r25,hi8(-(95))
	movw r22,r16
	ldi r20,lo8(10000)
	ldi r21,hi8(10000)
	movw r18,r28
	subi r18,lo8(-(20142))
	sbci r19,hi8(-(20142))
	rcall fibre_create
	.stabn	68,0,150,.LM54-.LFBB4
.LM54:
	rcall fibres_start
	.stabn	68,0,152,.LM55-.LFBB4
.LM55:
	ldi r24,lo8(.LC3)
	ldi r25,hi8(.LC3)
	rcall puts
	.stabn	68,0,155,.LM56-.LFBB4
.LM56:
	ldi r24,lo8(0)
	ldi r25,hi8(0)
/* epilogue start */
	subi r28,lo8(-(30141))
	sbci r29,hi8(-(30141))
	in __tmp_reg__,__SREG__
	cli
	out __SP_H__,r29
	out __SREG__,__tmp_reg__
	out __SP_L__,r28
	pop r28
	pop r29
	pop r17
	pop r16
	ret
	.size	main, .-main
	.stabs	"routineRegs:(0,18)=ar(0,19)=r(0,19);0;0177777;;0;2;(8,6)",128,0,141,1
	.stabs	"stack:(0,20)=ar(0,19);0;2;(0,21)=ar(0,19);0;9999;(0,2)",128,0,142,142
	.stabn	192,0,0,.LFBB4-.LFBB4
	.stabn	224,0,0,.Lscope4-.LFBB4
.Lscope4:
	.stabs	"",36,0,0,.Lscope4-.LFBB4
	.stabd	78,0,0
	.data
.LC4:
	.string	"Starting blah()"
.LC5:
	.string	"blah() count: %d\n"
	.text
	.stabs	"blah:F(0,15)",36,0,23,blah
	.stabs	"rt:P(0,16)",64,0,22,16
.global	blah
	.type	blah, @function
blah:
	.stabd	46,0,0
	.stabn	68,0,23,.LM57-.LFBB5
.LM57:
.LFBB5:
	push r16
	push r17
	push r29
	push r28
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
	movw r16,r24
	.stabn	68,0,25,.LM58-.LFBB5
.LM58:
	ldi r24,lo8(.LC4)
	ldi r25,hi8(.LC4)
	rcall puts
	.stabn	68,0,27,.LM59-.LFBB5
.LM59:
	rcall .
	rcall .
	ldi r24,lo8(.LC5)
	ldi r25,hi8(.LC5)
	in r30,__SP_L__
	in r31,__SP_H__
	std Z+2,r25
	std Z+1,r24
	std Z+4,__zero_reg__
	std Z+3,__zero_reg__
	rcall printf
.LBB8:
.LBB9:
	.stabn	68,0,10,.LM60-.LFBB5
.LM60:
	movw r30,r16
	ldd r18,Z+38
	ori r18,lo8(2)
	std Z+38,r18
	.stabn	68,0,11,.LM61-.LFBB5
.LM61:
	ldi r24,lo8(gs(.L21))
	ldi r25,hi8(gs(.L21))
	std Z+37,r25
	std Z+36,r24
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
.L21:
	.stabn	68,0,13,.LM62-.LFBB5
.LM62:
	sbrs r18,1
	rjmp .L22
	.stabn	68,0,17,.LM63-.LFBB5
.LM63:
/* #APP */
 ;  17 "test.c" 1
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
in __tmp_reg__, __SP_H__
st Z+, __tmp_reg__
in __tmp_reg__, __SP_L__
st Z+, __tmp_reg__
st Z+, r29
st Z, r28

 ;  0 "" 2
	.stabn	68,0,18,.LM64-.LFBB5
.LM64:
/* #NOAPP */
	lds r30,mainRegs+36
	lds r31,(mainRegs+36)+1
/* #APP */
 ;  18 "test.c" 1
	ijmp
 ;  0 "" 2
/* #NOAPP */
.L22:
.LBE9:
.LBE8:
	.stabn	68,0,31,.LM65-.LFBB5
.LM65:
	rcall .
	rcall .
	ldi r24,lo8(.LC5)
	ldi r25,hi8(.LC5)
	in r30,__SP_L__
	in r31,__SP_H__
	std Z+2,r25
	std Z+1,r24
	ldi r24,lo8(1)
	ldi r25,hi8(1)
	std Z+4,r25
	std Z+3,r24
	rcall printf
.LBB10:
.LBB11:
	.stabn	68,0,10,.LM66-.LFBB5
.LM66:
	movw r30,r16
	ldd r18,Z+38
	ori r18,lo8(2)
	std Z+38,r18
	.stabn	68,0,11,.LM67-.LFBB5
.LM67:
	ldi r24,lo8(gs(.L23))
	ldi r25,hi8(gs(.L23))
	std Z+37,r25
	std Z+36,r24
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
.L23:
	.stabn	68,0,13,.LM68-.LFBB5
.LM68:
	sbrs r18,1
	rjmp .L24
	.stabn	68,0,17,.LM69-.LFBB5
.LM69:
/* #APP */
 ;  17 "test.c" 1
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
in __tmp_reg__, __SP_H__
st Z+, __tmp_reg__
in __tmp_reg__, __SP_L__
st Z+, __tmp_reg__
st Z+, r29
st Z, r28

 ;  0 "" 2
	.stabn	68,0,18,.LM70-.LFBB5
.LM70:
/* #NOAPP */
	lds r30,mainRegs+36
	lds r31,(mainRegs+36)+1
/* #APP */
 ;  18 "test.c" 1
	ijmp
 ;  0 "" 2
/* #NOAPP */
.L24:
.LBE11:
.LBE10:
	.stabn	68,0,35,.LM71-.LFBB5
.LM71:
	rcall .
	rcall .
	ldi r24,lo8(.LC5)
	ldi r25,hi8(.LC5)
	in r30,__SP_L__
	in r31,__SP_H__
	std Z+2,r25
	std Z+1,r24
	ldi r24,lo8(2)
	ldi r25,hi8(2)
	std Z+4,r25
	std Z+3,r24
	rcall printf
.LBB12:
.LBB13:
	.stabn	68,0,10,.LM72-.LFBB5
.LM72:
	movw r30,r16
	ldd r18,Z+38
	ori r18,lo8(2)
	std Z+38,r18
	.stabn	68,0,11,.LM73-.LFBB5
.LM73:
	ldi r24,lo8(gs(.L25))
	ldi r25,hi8(gs(.L25))
	std Z+37,r25
	std Z+36,r24
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
.L25:
	.stabn	68,0,13,.LM74-.LFBB5
.LM74:
	sbrs r18,1
	rjmp .L26
	.stabn	68,0,17,.LM75-.LFBB5
.LM75:
/* #APP */
 ;  17 "test.c" 1
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
in __tmp_reg__, __SP_H__
st Z+, __tmp_reg__
in __tmp_reg__, __SP_L__
st Z+, __tmp_reg__
st Z+, r29
st Z, r28

 ;  0 "" 2
	.stabn	68,0,18,.LM76-.LFBB5
.LM76:
/* #NOAPP */
	lds r30,mainRegs+36
	lds r31,(mainRegs+36)+1
/* #APP */
 ;  18 "test.c" 1
	ijmp
 ;  0 "" 2
/* #NOAPP */
.L26:
.LBE13:
.LBE12:
	.stabn	68,0,39,.LM77-.LFBB5
.LM77:
	rcall .
	rcall .
	ldi r24,lo8(.LC5)
	ldi r25,hi8(.LC5)
	in r30,__SP_L__
	in r31,__SP_H__
	std Z+2,r25
	std Z+1,r24
	ldi r24,lo8(3)
	ldi r25,hi8(3)
	std Z+4,r25
	std Z+3,r24
	rcall printf
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
/* epilogue start */
	.stabn	68,0,40,.LM78-.LFBB5
.LM78:
	pop r28
	pop r29
	pop r17
	pop r16
	ret
	.size	blah, .-blah
.Lscope5:
	.stabs	"",36,0,0,.Lscope5-.LFBB5
	.stabd	78,0,0
	.lcomm mainRegs,47
	.stabs	"mainRegs:S(0,22)=B(8,6)",40,0,5,mainRegs
	.stabs	"",100,0,0,.Letext0
.Letext0:
