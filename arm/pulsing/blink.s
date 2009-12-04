	.file	"blink.c"
	.section	.debug_abbrev,"",%progbits
.Ldebug_abbrev0:
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.text
.Ltext0:
	.align	2
	.global	delay
	.type	delay, %function
delay:
.LFB2:
	.file 1 "blink.c"
	.loc 1 9 0
	@ args = 0, pretend = 0, frame = 4
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
.LCFI0:
	stmfd	sp!, {fp, ip, lr, pc}
.LCFI1:
	sub	fp, ip, #4
.LCFI2:
	sub	sp, sp, #4
.LCFI3:
	.loc 1 12 0
	mov	r3, #0
	str	r3, [fp, #-16]
	b	.L2
.L3:
	.loc 1 13 0
	nop
	.loc 1 12 0
	ldr	r3, [fp, #-16]
	add	r3, r3, #1
	str	r3, [fp, #-16]
.L2:
	ldr	r2, [fp, #-16]
	mov	r3, #131072
	sub	r3, r3, #1
	cmp	r2, r3
	ble	.L3
	.loc 1 14 0
	ldmfd	sp, {r3, fp, sp, pc}
.LFE2:
	.size	delay, .-delay
	.align	2
	.global	main
	.type	main, %function
main:
.LFB3:
	.loc 1 18 0
	@ args = 0, pretend = 0, frame = 4
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
.LCFI4:
	stmfd	sp!, {fp, ip, lr, pc}
.LCFI5:
	sub	fp, ip, #4
.LCFI6:
	sub	sp, sp, #4
.LCFI7:
	.loc 1 21 0
	mov	r3, #-1610612736
	mov	r3, r3, asr #19
	str	r3, [fp, #-16]
	.loc 1 24 0
	ldr	r2, [fp, #-16]
	mov	r3, #393216
	add	r3, r3, #4
	str	r3, [r2, #0]
	.loc 1 27 0
	ldr	r2, [fp, #-16]
	mov	r3, #393216
	add	r3, r3, #4
	str	r3, [r2, #16]
.L7:
	.loc 1 33 0
	ldr	r2, [fp, #-16]
	mov	r3, #262144
	str	r3, [r2, #48]
	.loc 1 34 0
	ldr	r2, [fp, #-16]
	mov	r3, #131072
	str	r3, [r2, #52]
	.loc 1 36 0
	bl	delay
	.loc 1 39 0
	ldr	r2, [fp, #-16]
	mov	r3, #131072
	str	r3, [r2, #48]
	.loc 1 40 0
	ldr	r2, [fp, #-16]
	mov	r3, #262144
	str	r3, [r2, #52]
	.loc 1 42 0
	bl	delay
	.loc 1 43 0
	b	.L7
.LFE3:
	.size	main, .-main
	.section	.debug_frame,"",%progbits
.Lframe0:
	.4byte	.LECIE0-.LSCIE0
.LSCIE0:
	.4byte	0xffffffff
	.byte	0x1
	.ascii	"\000"
	.uleb128 0x1
	.sleb128 -4
	.byte	0xe
	.byte	0xc
	.uleb128 0xd
	.uleb128 0x0
	.align	2
.LECIE0:
.LSFDE0:
	.4byte	.LEFDE0-.LASFDE0
.LASFDE0:
	.4byte	.Lframe0
	.4byte	.LFB2
	.4byte	.LFE2-.LFB2
	.byte	0x4
	.4byte	.LCFI0-.LFB2
	.byte	0xd
	.uleb128 0xc
	.byte	0x4
	.4byte	.LCFI1-.LCFI0
	.byte	0x8e
	.uleb128 0x2
	.byte	0x8d
	.uleb128 0x3
	.byte	0x8b
	.uleb128 0x4
	.byte	0x4
	.4byte	.LCFI2-.LCFI1
	.byte	0xc
	.uleb128 0xb
	.uleb128 0x4
	.align	2
.LEFDE0:
.LSFDE2:
	.4byte	.LEFDE2-.LASFDE2
.LASFDE2:
	.4byte	.Lframe0
	.4byte	.LFB3
	.4byte	.LFE3-.LFB3
	.byte	0x4
	.4byte	.LCFI4-.LFB3
	.byte	0xd
	.uleb128 0xc
	.byte	0x4
	.4byte	.LCFI5-.LCFI4
	.byte	0x8e
	.uleb128 0x2
	.byte	0x8d
	.uleb128 0x3
	.byte	0x8b
	.uleb128 0x4
	.byte	0x4
	.4byte	.LCFI6-.LCFI5
	.byte	0xc
	.uleb128 0xb
	.uleb128 0x4
	.align	2
.LEFDE2:
	.text
.Letext0:
	.section	.debug_loc,"",%progbits
.Ldebug_loc0:
.LLST0:
	.4byte	.LFB2-.Ltext0
	.4byte	.LCFI0-.Ltext0
	.2byte	0x1
	.byte	0x5d
	.4byte	.LCFI0-.Ltext0
	.4byte	.LCFI2-.Ltext0
	.2byte	0x1
	.byte	0x5c
	.4byte	.LCFI2-.Ltext0
	.4byte	.LFE2-.Ltext0
	.2byte	0x2
	.byte	0x7b
	.sleb128 4
	.4byte	0x0
	.4byte	0x0
.LLST1:
	.4byte	.LFB3-.Ltext0
	.4byte	.LCFI4-.Ltext0
	.2byte	0x1
	.byte	0x5d
	.4byte	.LCFI4-.Ltext0
	.4byte	.LCFI6-.Ltext0
	.2byte	0x1
	.byte	0x5c
	.4byte	.LCFI6-.Ltext0
	.4byte	.LFE3-.Ltext0
	.2byte	0x2
	.byte	0x7b
	.sleb128 4
	.4byte	0x0
	.4byte	0x0
	.file 2 "AT91SAM7S256.h"
	.section	.debug_info
	.4byte	0x3ef
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.ascii	"GNU C 4.2.4\000"
	.byte	0x1
	.ascii	"blink.c\000"
	.ascii	"/home/scuzzy/Desktop/ARMBlinkExample\000"
	.4byte	.Ltext0
	.4byte	.Letext0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.4byte	0x57
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.ascii	"unsigned int\000"
	.uleb128 0x4
	.byte	0x4
	.byte	0x7
	.uleb128 0x5
	.4byte	0x57
	.4byte	0x7a
	.uleb128 0x6
	.4byte	0x67
	.byte	0x0
	.byte	0x0
	.uleb128 0x5
	.4byte	0x57
	.4byte	0x8a
	.uleb128 0x6
	.4byte	0x67
	.byte	0x8
	.byte	0x0
	.uleb128 0x7
	.ascii	"_AT91S_PIO\000"
	.byte	0xac
	.byte	0x2
	.2byte	0x162
	.4byte	0x35b
	.uleb128 0x8
	.ascii	"PIO_PER\000"
	.byte	0x2
	.2byte	0x163
	.4byte	0x52
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x8
	.ascii	"PIO_PDR\000"
	.byte	0x2
	.2byte	0x164
	.4byte	0x52
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x8
	.ascii	"PIO_PSR\000"
	.byte	0x2
	.2byte	0x165
	.4byte	0x52
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0x8
	.ascii	"Reserved0\000"
	.byte	0x2
	.2byte	0x166
	.4byte	0x35b
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0x8
	.ascii	"PIO_OER\000"
	.byte	0x2
	.2byte	0x167
	.4byte	0x52
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0x8
	.ascii	"PIO_ODR\000"
	.byte	0x2
	.2byte	0x168
	.4byte	0x52
	.byte	0x2
	.byte	0x23
	.uleb128 0x14
	.uleb128 0x8
	.ascii	"PIO_OSR\000"
	.byte	0x2
	.2byte	0x169
	.4byte	0x52
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0x8
	.ascii	"Reserved1\000"
	.byte	0x2
	.2byte	0x16a
	.4byte	0x360
	.byte	0x2
	.byte	0x23
	.uleb128 0x1c
	.uleb128 0x8
	.ascii	"PIO_IFER\000"
	.byte	0x2
	.2byte	0x16b
	.4byte	0x52
	.byte	0x2
	.byte	0x23
	.uleb128 0x20
	.uleb128 0x8
	.ascii	"PIO_IFDR\000"
	.byte	0x2
	.2byte	0x16c
	.4byte	0x52
	.byte	0x2
	.byte	0x23
	.uleb128 0x24
	.uleb128 0x8
	.ascii	"PIO_IFSR\000"
	.byte	0x2
	.2byte	0x16d
	.4byte	0x52
	.byte	0x2
	.byte	0x23
	.uleb128 0x28
	.uleb128 0x8
	.ascii	"Reserved2\000"
	.byte	0x2
	.2byte	0x16e
	.4byte	0x365
	.byte	0x2
	.byte	0x23
	.uleb128 0x2c
	.uleb128 0x8
	.ascii	"PIO_SODR\000"
	.byte	0x2
	.2byte	0x16f
	.4byte	0x52
	.byte	0x2
	.byte	0x23
	.uleb128 0x30
	.uleb128 0x8
	.ascii	"PIO_CODR\000"
	.byte	0x2
	.2byte	0x170
	.4byte	0x52
	.byte	0x2
	.byte	0x23
	.uleb128 0x34
	.uleb128 0x8
	.ascii	"PIO_ODSR\000"
	.byte	0x2
	.2byte	0x171
	.4byte	0x52
	.byte	0x2
	.byte	0x23
	.uleb128 0x38
	.uleb128 0x8
	.ascii	"PIO_PDSR\000"
	.byte	0x2
	.2byte	0x172
	.4byte	0x52
	.byte	0x2
	.byte	0x23
	.uleb128 0x3c
	.uleb128 0x8
	.ascii	"PIO_IER\000"
	.byte	0x2
	.2byte	0x173
	.4byte	0x52
	.byte	0x2
	.byte	0x23
	.uleb128 0x40
	.uleb128 0x8
	.ascii	"PIO_IDR\000"
	.byte	0x2
	.2byte	0x174
	.4byte	0x52
	.byte	0x2
	.byte	0x23
	.uleb128 0x44
	.uleb128 0x8
	.ascii	"PIO_IMR\000"
	.byte	0x2
	.2byte	0x175
	.4byte	0x52
	.byte	0x2
	.byte	0x23
	.uleb128 0x48
	.uleb128 0x8
	.ascii	"PIO_ISR\000"
	.byte	0x2
	.2byte	0x176
	.4byte	0x52
	.byte	0x2
	.byte	0x23
	.uleb128 0x4c
	.uleb128 0x8
	.ascii	"PIO_MDER\000"
	.byte	0x2
	.2byte	0x177
	.4byte	0x52
	.byte	0x2
	.byte	0x23
	.uleb128 0x50
	.uleb128 0x8
	.ascii	"PIO_MDDR\000"
	.byte	0x2
	.2byte	0x178
	.4byte	0x52
	.byte	0x2
	.byte	0x23
	.uleb128 0x54
	.uleb128 0x8
	.ascii	"PIO_MDSR\000"
	.byte	0x2
	.2byte	0x179
	.4byte	0x52
	.byte	0x2
	.byte	0x23
	.uleb128 0x58
	.uleb128 0x8
	.ascii	"Reserved3\000"
	.byte	0x2
	.2byte	0x17a
	.4byte	0x36a
	.byte	0x2
	.byte	0x23
	.uleb128 0x5c
	.uleb128 0x8
	.ascii	"PIO_PPUDR\000"
	.byte	0x2
	.2byte	0x17b
	.4byte	0x52
	.byte	0x2
	.byte	0x23
	.uleb128 0x60
	.uleb128 0x8
	.ascii	"PIO_PPUER\000"
	.byte	0x2
	.2byte	0x17c
	.4byte	0x52
	.byte	0x2
	.byte	0x23
	.uleb128 0x64
	.uleb128 0x8
	.ascii	"PIO_PPUSR\000"
	.byte	0x2
	.2byte	0x17d
	.4byte	0x52
	.byte	0x2
	.byte	0x23
	.uleb128 0x68
	.uleb128 0x8
	.ascii	"Reserved4\000"
	.byte	0x2
	.2byte	0x17e
	.4byte	0x36f
	.byte	0x2
	.byte	0x23
	.uleb128 0x6c
	.uleb128 0x8
	.ascii	"PIO_ASR\000"
	.byte	0x2
	.2byte	0x17f
	.4byte	0x52
	.byte	0x2
	.byte	0x23
	.uleb128 0x70
	.uleb128 0x8
	.ascii	"PIO_BSR\000"
	.byte	0x2
	.2byte	0x180
	.4byte	0x52
	.byte	0x2
	.byte	0x23
	.uleb128 0x74
	.uleb128 0x8
	.ascii	"PIO_ABSR\000"
	.byte	0x2
	.2byte	0x181
	.4byte	0x52
	.byte	0x2
	.byte	0x23
	.uleb128 0x78
	.uleb128 0x8
	.ascii	"Reserved5\000"
	.byte	0x2
	.2byte	0x182
	.4byte	0x374
	.byte	0x2
	.byte	0x23
	.uleb128 0x7c
	.uleb128 0x8
	.ascii	"PIO_OWER\000"
	.byte	0x2
	.2byte	0x183
	.4byte	0x52
	.byte	0x3
	.byte	0x23
	.uleb128 0xa0
	.uleb128 0x8
	.ascii	"PIO_OWDR\000"
	.byte	0x2
	.2byte	0x184
	.4byte	0x52
	.byte	0x3
	.byte	0x23
	.uleb128 0xa4
	.uleb128 0x8
	.ascii	"PIO_OWSR\000"
	.byte	0x2
	.2byte	0x185
	.4byte	0x52
	.byte	0x3
	.byte	0x23
	.uleb128 0xa8
	.byte	0x0
	.uleb128 0x2
	.4byte	0x6a
	.uleb128 0x2
	.4byte	0x6a
	.uleb128 0x2
	.4byte	0x6a
	.uleb128 0x2
	.4byte	0x6a
	.uleb128 0x2
	.4byte	0x6a
	.uleb128 0x2
	.4byte	0x7a
	.uleb128 0x9
	.ascii	"AT91PS_PIO\000"
	.byte	0x2
	.2byte	0x186
	.4byte	0x38c
	.uleb128 0xa
	.byte	0x4
	.4byte	0x8a
	.uleb128 0xb
	.byte	0x1
	.ascii	"delay\000"
	.byte	0x1
	.byte	0x9
	.4byte	.LFB2
	.4byte	.LFE2
	.4byte	.LLST0
	.4byte	0x3b9
	.uleb128 0xc
	.ascii	"i\000"
	.byte	0x1
	.byte	0xa
	.4byte	0x3b9
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.byte	0x0
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0xd
	.byte	0x1
	.ascii	"main\000"
	.byte	0x1
	.byte	0x12
	.4byte	0x3b9
	.4byte	.LFB3
	.4byte	.LFE3
	.4byte	.LLST1
	.4byte	0x3ed
	.uleb128 0xc
	.ascii	"pPIO\000"
	.byte	0x1
	.byte	0x15
	.4byte	0x3ed
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.byte	0x0
	.uleb128 0x2
	.4byte	0x379
	.byte	0x0
	.section	.debug_abbrev
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0x8
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x1b
	.uleb128 0x8
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0x0
	.byte	0x0
	.uleb128 0x2
	.uleb128 0x35
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0x0
	.byte	0x0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x6
	.uleb128 0x21
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x7
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x8
	.uleb128 0xd
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x9
	.uleb128 0x16
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xa
	.uleb128 0xf
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xb
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xc
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0xd
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.section	.debug_pubnames,"",%progbits
	.4byte	0x21
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x3f3
	.4byte	0x392
	.ascii	"delay\000"
	.4byte	0x3c0
	.ascii	"main\000"
	.4byte	0x0
	.section	.debug_aranges,"",%progbits
	.4byte	0x1c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0x0
	.2byte	0x0
	.2byte	0x0
	.4byte	.Ltext0
	.4byte	.Letext0-.Ltext0
	.4byte	0x0
	.4byte	0x0
	.ident	"GCC: (GNU) 4.2.4"
