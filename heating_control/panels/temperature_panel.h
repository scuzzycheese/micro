#include <avr/io.h>
#include <stdio.h>
#include "lcdClass.h"
#include "adc/adc.h"

#ifndef _TEMPERATURE_PANEL_H
#define _TEMPERATURE_PANEL_H


struct temperaturePanel
{
   uint8_t panelNumber;
   struct lcdDriver *lcdDriver;

};


void drawTemperaturePanel(struct temperaturePanel *this);

#endif
