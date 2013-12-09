#include <avr/io.h>
#include <inttypes.h>
#define F_CPU 16000000UL  // 16 MHz#include <avr/interrupt.h>
#include <util/delay.h>
#include <geyserwise.h>

volatile enum
{
   UNKNOWN,
   STARTED,
   STOPPED
} TIMERSTATE;

ISR(INT0_vect)
{
   cli();

   //Also have to check the state of the pin
   if(TIMERSTATE == STOPPED || TIMERSTATE == UNKNOWN)
   {
      TCNT1 = 0x00;
      //start the timer
      //prescaler of clk/1024, 16mil/1024 = 15625 increments per second
      TCCR1B = (1 << CS10) | (1 << CS12);
      TIMERSTATE = STARTED;
   }

   //Also have to check the state of the pin
   if(TIMERSTATE == STARTED)
   {
      //Stop the timer
      TCCR1B = 0x00;
      uint16_t timerVal = TCNT1;
      TIMERSTATE = STOPPED;
   }


   //clear any new interrupt flags
   GIFR |= 1 << INTF0;
   sei();
}

void
delay_ms(unsigned int ms)
/* delay for a minimum of <ms> */
{
   // we use a calibrated macro. This is more
   // accurate and not so much compiler dependent
   // as self made code.
   while(ms)
   {
      _delay_ms(0.96);
      ms--;
   }
}

int
main(void)
{

   DDRC = (1 << PORTC0);

   PORTC = 1;

   //power down the ADC conversion
   ACSR |= (1 << ACD);

   MCUCR = (1 << ISC10);

   sei();

   while(1)
   {
   }

   return 0;
}
