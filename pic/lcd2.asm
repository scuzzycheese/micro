INCLUDE "p16f84a.inc"

;set up my registers
W                            EQU     H'0000'
F                            EQU     H'0001'
STATUS                       EQU     H'0003'
PORTA                        EQU     H'0005'
PORTB                        EQU     H'0006'
TRISA                        EQU     H'0085'
TRISB                        EQU     H'0086'
RP0                          EQU     H'0005'
;lcd specific stuff
LCD_DATA				EQU PORTB
LCD_DATA_TRIS		EQU TRISB
LCD_TEMPH			EQU 0x20
LCD_TEMPL			EQU 0x21
LCD_TEMP				EQU 0x22
DELAY					EQU 0x23
X_DELAY				EQU 0x24
DATACTRL				EQU 0x25

LCD_RS				EQU 4
LCD_RW				EQU 2
LCD_E					EQU 3

LCD_LINE0			EQU 0x00
LCD_LINE1			EQU 0x40
LCD_LINE2			EQU 0x14
LCD_LINE3			EQU 0x54

LCD_CLR				EQU B'00000001'

;the chip (or writer) needs these

	__CONFIG        _CP_OFF & _PWRTE_ON & _WDT_OFF & _XT_OSC


             
	ORG 0
	GOTO Boot

LCDINIT4BIT
	MOVLW 0x01E
	CALL X_DELAY500						; 30 * 0.5mS = 15mS

	MOVLW 0x20								; 4 bit mode(00100000)
	MOVWF LCD_TEMP							; put this data into a temp vaf
	BSF	LCD_TEMP, LCD_E				; LCD E-line high
	MOVF	LCD_TEMP, W
	MOVWF	LCD_DATA
	BCF	LCD_DATA, LCD_E				; LCD E-line low

	CALL PUTCMD								; indicate we are putting a command to the system
	MOVLW LCD_CLR							; move the data we want to send into the W register
	CALL LCDSEND							; send the data to the lcd display

	RETURN


DDRAMSTART
	CALL			PUTCMD					; indicate we are sending a command
	MOVLW			B'10000000'				; indicates the start of the address memory
	CALL			LCDSEND					; send the data to the lcd
	RETURN
	

PUTCMD
	MOVLW			0x00
	MOVWF			DATACTRL					; Reset our data control settings
	BCF			DATACTRL, LCD_RW		; Set LCD in read mode
	BCF			DATACTRL, LCD_RS		; Set LCD in command mode
	BSF			DATACTRL, LCD_E		; LCD E-line high
	RETURN

PUTCHAR
	MOVLW			0x00
	MOVWF			DATACTRL					; Reset our data control settings
	BCF			DATACTRL, LCD_RW		; Set LCD in read mode
	BSF			DATACTRL, LCD_RS		; Set LCD in data mode
	BSF			DATACTRL, LCD_E		; LCD E-line high
	RETURN


LCDSEND
	MOVWF			LCD_TEMP

	MOVF			LCD_TEMP, W				; Move the data into W (don't need this, the val is already in W)
	IORLW			0x0F						; Keep only the low nibble
	MOVWF			LCD_TEMPL				; Set tempL to the low nibble
	SWAPF			LCD_TEMPL, F			; push the low nibble into the high part of the byte

	MOVF			LCD_TEMP, W				; Move the data into W again
	IORLW			0xF0						; Keep only the high nibble
	MOVWF			LCD_TEMPH				; set tempH to the high nibble
		
	MOVF			DATACTRL, W				; Move our data controll
	MOVWF			LCD_TEMP					; into temp

	;CALL			LCDBUSY					; Wait for LCD to be ready
	CALL X_DELAY500

	MOVF			LCD_TEMPL, W			; Move Low nibble data to W
	ANDWF			LCD_TEMP, W				; Set up the bits for communicating	and store whole byte in W
	MOVWF			LCD_DATA					; Send data to LCD

	MOVF			LCD_TEMPH, W			; Move High nible data to W
	ANDWF			LCD_TEMP, W				; Set up the bits for communicating and store whole byte in W
	MOVWF			LCD_DATA					; Send data to LCD

	BCF			LCD_DATA, LCD_E		; LCD E-line Low
	RETURN



;***********************************  a 500uS delay @ 4MHz X-tal
DELAY500
    MOVLW       D'165'              ; +1        1 cycle
    MOVWF       DELAY               ; +2        1 cycle
DELAY500_LOOP
    DECFSZ      DELAY, F            ; step1     1 cycle
    GOTO        DELAY500_LOOP       ; step2     2 cycles
DELAY500_END
    RETURN                          ; +3        2 cycles

;***********************************  a delay of 'W' * 500mS
X_DELAY500
    MOVWF       X_DELAY             ; +1        1 cycle
X_DELAY500_LOOP
    CALL        DELAY500            ; step1     wait 500uSec
    DECFSZ      X_DELAY, F          ; step2     1 cycle
    GOTO        X_DELAY500_LOOP     ; step3     2 cycles
X_DELAY500_END
    RETURN                          ; +2        2 cycles


Boot	
	BSF   STATUS, RP0 ;go to bank 1

	MOVLW B'00000000'
	MOVWF TRISB

	BCF	STATUS, RP0 ;go to bank 0

	CALL LCDINIT4BIT 			; init the display in 4 bit mode

START
	CALL DDRAMSTART			; Set the ram for the start

	CALL PUTCHAR				; indicate we are sending data to the display	
	MOVLW 0x82					; move the data we wannt send into the w regist
	CALL LCDSEND				; send it

	MOVLW	0xFF
	CALL X_DELAY500

PSEUDOEND
	GOTO PSEUDOEND

	GOTO START

END
