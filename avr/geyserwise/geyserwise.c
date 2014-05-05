#include <avr/io.h>
#include <inttypes.h>
#define F_CPU 16000000UL  // 16 MHz#include <avr/interrupt.h>
#include <util/delay.h>
#include <geyserwise.h>


volatile struct
{
      uint8_t resetCondition : 1;
      uint8_t startCondition : 1;
      uint8_t dataBitCounter : 4;
      uint8_t dataByteCounter : 2;
} conditionState = {0, 0, 0, 0};

volatile uint16_t timerValUp = 0;
volatile uint16_t timerValDown = 0;
volatile uint8_t packetByte[4] = {0, 0, 0, 0};
volatile uint8_t tempValue = 0;

#define INTVAL (PIND & (1 << PORTD2))
#define START_TIMER TCCR1B = (1 << CS10) | (1 << CS12)
#define STOP_TIMER TCCR1B = 0x00

#define RESET_LENGTH 50
#define START_CONDITION_LENGTH 21
#define END_CONDITION_LENGTH 21
#define LONG_PULSE_LENGTH 10

ISR(INT0_vect)
{
   cli();

   //Also have to check the state of the pin
   if(INTVAL)
   {
      STOP_TIMER;
      timerValDown = TCNT1;
      TCNT1 = 0x00;
      timerValUp = 0;

      START_TIMER;
   }

   //Also have to check the state of the pin
   if(!INTVAL)
   {
      STOP_TIMER;
      timerValUp = TCNT1;
      TCNT1 = 0x00;
      timerValDown = 0;

      START_TIMER;
   }

   //We have encountered a reset condition, now move to a normal flow
   if(timerValUp > RESET_LENGTH)
   {
      conditionState.resetCondition = 1;
      conditionState.dataBitCounter = 0;
      conditionState.startCondition = 0;
      conditionState.dataByteCounter = 0;

      packetByte[0] = 0;
      packetByte[1] = 0;
      packetByte[2] = 0;
      packetByte[3] = 0;
   }

   //We are currently in a start condition
   if(timerValDown > START_CONDITION_LENGTH && conditionState.resetCondition == 1)
   {
      conditionState.startCondition = 1;
      conditionState.resetCondition = 0;
      return;
   }

   //Communication finished
   if(timerValUp > END_CONDITION_LENGTH && conditionState.resetCondition == 0)
   {
      conditionState.startCondition = 0;
      conditionState.resetCondition = 0;
   }

   if(conditionState.startCondition && conditionState.resetCondition == 0)
   {
      if(INTVAL)
      {
         if(timerValDown > LONG_PULSE_LENGTH)
         {
            packetByte[conditionState.dataByteCounter] |= (1 << conditionState.dataBitCounter);
         }

         if(conditionState.dataBitCounter >= 7)
         {
            //Here we gleen the correct data from the packets
             if(packetByte[0] == 0 && packetByte[2] == 0 && packetByte[3] == 24)
             {
                tempValue = packetByte[1] - 25;
             }

            //Probaly not nessesary
            conditionState.dataBitCounter = 0;
            if(conditionState.dataByteCounter >= 3)
            {
               conditionState.dataByteCounter = 0;
            }
            else
            {
               conditionState.dataByteCounter ++;
            }
         
         }
         else
         {
            conditionState.dataBitCounter ++;
         }
      }
   }


   //clear any new interrupt flags
   GIFR |= 1 << INTF0;
   sei();
}

void sendStart(void)
{
   PORTD |= (1 << PORTD2);
   _delay_ms(5);
   PORTD &= ~(1 << PORTD2);
   _delay_ms(1.5);
   PORTD |= (1 << PORTD2);
   _delay_ms(0.4);
}
void sendEnd(void)
{
   _delay_ms(1.1);
   PORTD &= ~(1 << PORTD2);
}

void send0(void)
{
   PORTD &= ~(1 << PORTD2);
   _delay_ms(0.4);
   PORTD |= (1 << PORTD2);
   _delay_ms(0.4);
}

void send1(void)
{
   PORTD &= ~(1 << PORTD2);
   _delay_ms(1.2);
   PORTD |= (1 << PORTD2);
   _delay_ms(0.4);
}

int main(void)
{

   DDRC = (1 << PORTC0);
   DDRD = (1 << PORTD2);
   DDRB = 0xFF;
   PORTB = 0;

//   PORTC = 1;

   //power down the ADC conversion
   ACSR |= (1 << ACD);

   GICR |= (1 << INT0);
   MCUCR |= (1 << ISC00);

   sei();

   while(1)
   {
      sendStart();

      send0();
      send0();
      send0();
      send0();
      send0();
      send0();
      send0();
      send0();

      send1();
      send0();
      send0();
      send1();
      send1();
      send0();
      send1();
      send0();

      send0();
      send0();
      send0();
      send0();
      send0();
      send0();
      send0();
      send0();

      send0();
      send0();
      send0();
      send1();
      send1();
      send0();
      send0();
      send0();

      sendEnd();

      _delay_us(47);

      sendStart();

      send0();
      send0();
      send0();
      send0();
      send0();
      send0();
      send0();
      send0();

      send1();
      send0();
      send0();
      send1();
      send1();
      send0();
      send1();
      send0();

      send0();
      send0();
      send0();
      send0();
      send0();
      send0();
      send0();
      send0();

      send0();
      send0();
      send0();
      send1();
      send1();
      send0();
      send0();
      send0();

      sendEnd();

      _delay_ms(1000);

      if(tempValue > 63)
      {
         PORTC |= (1 << PORTC0);
      }
   }

   return 0;
}

