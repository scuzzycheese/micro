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
LCD_CTRL				EQU PORTA
LCD_TEMP				EQU 0x20
DELAY					EQU 0x23
X_DELAY				EQU 0x24

LCD_E					EQU 2
LCD_RW				EQU 1
LCD_RS				EQU 0

LCD_LINE0			EQU 0x000
LCD_LINE1			EQU 0x040
LCD_LINE2			EQU 0x014
LCD_LINE3			EQU 0x054



;the chip (or writer) needs these

	__CONFIG        _CP_OFF & _PWRTE_ON & _WDT_OFF & _XT_OSC


             
	ORG 0
	GOTO Boot

LCDINIT
                                    ; Busy-flag is not yet valid
    CLRF        LCD_CTRL            ; ALL PORT output should output Low.
                                    ; power-up delay
    MOVLW       0x01E
    CALL        X_DELAY500          ; 30 * 0.5mS = 15mS
                                    ; Busy Flag should be valid from here
    MOVLW       0x038               ; 8-bit-interface, 2-lines
    CALL        LCDPUTCMD
    MOVLW       0x000               ; disp.off, curs.off, no-blink
    CALL        LCDDMODE
    CALL        LCDCLEAR
    MOVLW       0x004               ; disp.on, curs.off
    CALL        LCDDMODE
    MOVLW       0x002               ; auto-inc (shift-cursor)
    CALL        LCDEMODE
    RETURN


LCDBUSY

	;daine hack
    BSF		PORTA, 3;

    BSF         STATUS,RP0          ; Select Register page 1
    MOVLW       0x0FF               ; Set PORTB for input
    MOVWF       LCD_DATA_TRIS
    BCF         STATUS, RP0         ; Select Register page 0
    BCF         LCD_CTRL, LCD_RS    ; Set LCD for command mode
    BSF         LCD_CTRL, LCD_RW    ; Setup to read busy flag
    BSF         LCD_CTRL, LCD_E     ; LCD E-line High
    MOVF        LCD_DATA, W         ; Read busy flag + DDram address
    BCF         LCD_CTRL, LCD_E     ; LCD E-line Low
    ANDLW       0x80                ; Check Busy flag, High = Busy
    BTFSS       STATUS, Z
    GOTO        LCDBUSY
LCDNOTBUSY
    BCF         LCD_CTRL, LCD_RW
    BSF         STATUS, RP0         ; Select Register page 1
    MOVLW       0x000
    MOVWF       LCD_DATA_TRIS       ; Set PORTB for output
    BCF         STATUS, RP0         ; Select Register page 0
    RETURN


LCDCLEAR
    MOVLW       0x001
    CALL        LCDPUTCMD
    RETURN


LCDHOME
    MOVLW       0x002
    CALL        LCDPUTCMD
    RETURN


LCDEMODE
    ANDLW       0x003               ; Strip upper bits
    IORLW       0x004               ; Function set
    CALL        LCDPUTCMD
    RETURN

LCDDMODE
    ANDLW       0x007               ; Strip upper bits
    IORLW       0x008               ; Function set
    CALL        LCDPUTCMD
    RETURN

LCDSCGA
    ANDLW       0x03F               ; Strip upper bits
    IORLW       0x040               ; Function set
    CALL        LCDPUTCMD
    RETURN

LCDSDDA
    IORLW       0x080               ; Function set
    CALL        LCDPUTCMD
    RETURN


LCDGADDR
    BSF         STATUS,RP0          ; Select Register page 1
    MOVLW       0x0FF               ; Set PORTB for input
    MOVWF       LCD_DATA_TRIS
    BCF         STATUS, RP0         ; Select Register page 0
    BCF         LCD_CTRL, LCD_RS    ; Set LCD for command mode
    BSF         LCD_CTRL, LCD_RW    ; Setup to read busy flag
    BSF         LCD_CTRL, LCD_E     ; LCD E-line High
    MOVF        LCD_DATA, W         ; Read busy flag + RAM address
    BCF         LCD_CTRL, LCD_E     ; LCD E-line Low
    ANDLW       0x07F               ; Strip upper bit
    BCF         LCD_CTRL, LCD_RW
    BSF         STATUS, RP0         ; Select Register page 1
    MOVLW       0x000
    MOVWF       LCD_DATA_TRIS       ; Set PORTB for output
    BCF         STATUS, RP0         ; Select Register page 0
    RETURN

LCDPUTCHAR
    MOVWF       LCD_TEMP            ; Character to send is in W
    CALL        LCDBUSY             ; Wait for LCD to be ready
    BCF         LCD_CTRL, LCD_RW    ; Set LCD in read mode
    BSF         LCD_CTRL, LCD_RS    ; Set LCD in data mode
    BSF         LCD_CTRL, LCD_E     ; LCD E-line High
    MOVF        LCD_TEMP, W
    MOVWF       LCD_DATA            ; Send data to LCD
    BCF         LCD_CTRL, LCD_E     ; LCD E-line Low
    RETURN

LCDPUTCMD
    MOVWF       LCD_TEMP            ; Command to send is in W
    CALL        LCDBUSY             ; Wait for LCD to be ready
    BCF         LCD_CTRL, LCD_RW    ; Set LCD in read mode
    BCF         LCD_CTRL, LCD_RS    ; Set LCD in command mode
    BSF         LCD_CTRL, LCD_E     ; LCD E-line High
    MOVF        LCD_TEMP, W
    MOVWF       LCD_DATA            ; Send data to LCD
    BCF         LCD_CTRL, LCD_E     ; LCD E-line Low
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
	MOVWF TRISA

	MOVLW B'00000000'
	MOVWF TRISB

	BSF	OPTION_REG, NOT_RBPU

	BCF	STATUS, RP0 ;go to bank 0

	CALL LCDINIT	;initialize LCD display

START
	MOVLW	LCD_LINE0
	CALL	LCDSDDA		;cursor to top left
	
	MOVLW 0x82
	CALL LCDPUTCHAR

	MOVLW	0xFF
	CALL X_DELAY500

PSEUDOEND
	GOTO PSEUDOEND

	GOTO START

END
