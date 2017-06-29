#ifndef ADC_H
#define ADC_H

#include <avr/io.h>
#include <stdio.h>
#include <math.h>


#define SERIESRESISTOR 100000.0
#define NOMINAL_RESISTANCE 100000.0
#define NOMINAL_TEMPERATURE 25.0
#define BCOEFFICIENT 3950.0


uint16_t readADC(void);
void enableADC(void);
void enableADC11(void);
void enableADC12(void);
void disableADC(void);
float steinhartValue(uint16_t adcValue);

#endif
