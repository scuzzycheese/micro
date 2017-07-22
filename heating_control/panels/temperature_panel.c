#include "temperature_panel.h"
#include "utils/utils.h"


void drawTemperaturePanel(struct temperaturePanel *this) 
{
   disableIndexer();
   this->lcdDriver->clearController(this->panelNumber);

   this->lcdDriver->printf(0, 0, "Tank: ");
   this->lcdDriver->printf(0, 8, "Pipe: ");
   enableIndexer();

   enableADC11();
   uint16_t adcValue = readADC();
   float steinhart = steinhartValue(adcValue);
   disableIndexer();
   this->lcdDriver->printf(34, 0, "%.2f", steinhart);
   enableIndexer();

   enableADC12();
   adcValue = readADC();
   steinhart = steinhartValue(adcValue);
   disableIndexer();
   this->lcdDriver->printf(34, 8, "%.2f", steinhart);


   this->lcdDriver->flushVM();
   enableIndexer();

}

