#include "temperature_panel.h"


void drawTemperaturePanel(struct temperaturePanel *this) 
{
   this->lcdDriver->clearController(this->panelNumber);

   this->lcdDriver->printf(0, 0, "Tank: ");
   this->lcdDriver->printf(0, 8, "Pipe: ");

   enableADC11();
   uint16_t adcValue = readADC();
   float steinhart = steinhartValue(adcValue);
   this->lcdDriver->printf(34, 0, "%.2f", steinhart);

   enableADC12();
   adcValue = readADC();
   steinhart = steinhartValue(adcValue);
   this->lcdDriver->printf(34, 8, "%.2f", steinhart);


   this->lcdDriver->flushVM();

}

