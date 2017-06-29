#include "adc/adc.h"

void enableADC()
{
   //turn on ADC
   ADCSRA |= _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
}

void enableADC11() 
{
   //configure the ADC ports
   ADMUX = _BV(REFS0) | _BV(ADLAR) | _BV(MUX0) | _BV(MUX1);
   ADCSRB |= _BV(MUX5);
}

void enableADC12() 
{
   //configure the ADC ports
   ADMUX = _BV(REFS0) | _BV(ADLAR) | _BV(MUX2);
   ADCSRB |= _BV(MUX5);
}

void disableACD() 
{
   ADCSRA &= ~(_BV(ADEN));
}

uint16_t readADC() 
{

   ADCSRA |= _BV(ADSC); // Start conversion
   while (bit_is_set(ADCSRA,ADSC)); // measuring

   uint8_t low  = ADCL; // must read ADCL first - it then locks ADCH  
   uint8_t high = ADCH; // unlocks both


   uint16_t result = (low >> 6) | (high << 2);

   //result = 2250600L / result; // Calculate Vcc (in mV); 1125300 = 1.1*1023*1000
   return result; // Vcc in millivolts
}

float steinhartValue(uint16_t adcValue)
{
   float resistance = (1023.0 / (float)adcValue) - 1;
   //91.8k is the tested value of the resistor
   resistance = 91800.0 / resistance;

   float steinhart;
   steinhart = resistance / NOMINAL_RESISTANCE; // (R/Ro)
   steinhart = log(steinhart); // ln(R/Ro)
   steinhart /= BCOEFFICIENT; // 1/B * ln(R/Ro)
   steinhart += 1.0 / (NOMINAL_TEMPERATURE + 273.15); // + (1/To)
   steinhart = 1.0 / steinhart; // Invert
   steinhart -= 273.15; // convert to C

   return steinhart;
}

