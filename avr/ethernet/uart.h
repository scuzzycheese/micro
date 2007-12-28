#include "FCPU.h"
#include <avr/interrupt.h>

#define SET_BAUD(baudRate) (((F_CPU / baudRate) / 16L) - 1);

void usart_init();
inline void putChar(uint8_t c);
void writeLn(char *strn);
void writeLnLen(char *data, int len);
