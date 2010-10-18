#include "FCPU.h"
#include "inttypes.h"
#ifndef X86
#include <avr/interrupt.h>
#endif

#define SET_BAUD(baudRate) (((F_CPU / baudRate) / 16L) - 1);

void usart_init();
void putChar(uint8_t c);
void writeLn(char *strn);
void writeLnLen(char *data, int len);
