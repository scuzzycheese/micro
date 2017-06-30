#include <avr/io.h>
#include <util/delay.h>

#ifndef D22_5003H
#define D22_5003H


#define D22_DBOUT PORTD
#define D22_DBIN PIND
#define D22_DB_DDR DDRD

#define D22_CONTROL_PORT PORTB
#define D22_CONTROL_DDR DDRB

#define D22_READ_PIN PORTB0
#define D22_WRITE_PIN PORTB1
#define D22_REGISTER_SELECT_PIN PORTB2
#define D22_CS_PIN PORTB3




void D22Init();
uint8_t D22WriteByte(uint8_t byte);



#define D22_SET_READ D22_CONTROL_PORT = (D22_CONTROL_PORT & ~((1 << D22_READ_PIN) | (1 << D22_WRITE_PIN))) | (1 << D22_READ_PIN)
#define D22_CLEAR_READ D22_CONTROL_PORT &= ~((1 << D22_READ_PIN) | (1 << D22_WRITE_PIN))

#define D22_SET_WRITE D22_CONTROL_PORT = (D22_CONTROL_PORT & ~((1 << D22_READ_PIN) | (1 << D22_WRITE_PIN))) | (1 << D22_WRITE_PIN)
#define D22_CLEAR_WRITE D22_CONTROL_PORT &= ~((1 << D22_READ_PIN) | (1 << D22_WRITE_PIN))

#define D22_SET_DISPLAY_DATA D22_CONTROL_PORT |= (1 << D22_REGISTER_SELECT_PIN)
#define D22_SET_CONTROL_DATA D22_CONTROL_PORT &= ~(1 << D22_REGISTER_SELECT_PIN)

#endif