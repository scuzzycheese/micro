#include <avr/io.h>
#include <stdio.h>
#include "lcdClass.h"
#include "adc/adc.h"
#include "DS1302/DS1302.h"
#include "timeUtils/timeUtils.h"

#ifndef _TIME_PANEL_H
#define _TIME_PANEL_H

struct timePanel
{
   uint8_t panelNumber;
   struct lcdDriver *lcdDriver;
};

void drawTimePanel(struct timePanel *this);

#endif
