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


;the chip (or writer) needs these

	__CONFIG        _CP_OFF & _PWRTE_ON & _WDT_OFF & _XT_OSC


;randoms vars

TIMER1		EQU	H'20'		;Used in delay routine
TIMER2		EQU	H'21'		; "	"	"	
DECVAL		EQU	H'0D'		; Something fun
SCRATCH		EQU	H'0E'		; random scratch variable

              
	ORG 0
	GOTO Boot

;character lookup table

CHARLKUP
	ADDWF PCL, 1
	DT	0xFF, 0xFF, 0x30, 0x30, 0x30, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xC3, 0xC3, 0xC3, 0xFF, 0xFF, 0xC3, 0xC3, 0xC3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ;smiley face
	GOTO Start
CHARLKUP_end


;delay routine

DELAY_ROUTINE   MOVLW   D'2'         ;54 Generate approx 10mS delay at 4Mhz CLK
                MOVWF   TIMER2
DEL_LOOP1       MOVLW   D'255'	       ;60	
                MOVWF   TIMER1
DEL_LOOP2       DECFSZ  TIMER1, F
                GOTO    DEL_LOOP2
                DECFSZ  TIMER2, F
                GOTO    DEL_LOOP1
		RETLW   0



Boot	BSF	STATUS, RP0	;go to bank 1

	MOVLW	B'00000000'	;make sure pins RB0-RB7 are output
	MOVWF	TRISB		
				
	BCF	STATUS, RP0	;back to bank 0

Start

	MOVLW 0
	MOVWF SCRATCH
	MOVLW 0
	MOVWF PORTB

IntLoop

	CALL CHARLKUP						;Get our smiley, i think
	MOVWF PORTB							;Move what I think is the first colum to port B

	CALL DELAY_ROUTINE				;Let that colum stay there for a bit

	INCFSZ SCRATCH, F					;increment scratch by one
	MOVF SCRATCH, W

	GOTO IntLoop
	GOTO Start
	END
