#include "time_panel.h"



void drawTimePanel(struct timePanel *this) 
{
   uint8_t seconds = DS1302ReadSeconds();
   uint8_t minutes = DS1302ReadMinutes();
   uint8_t hours = DS1302ReadHours();


   this->lcdDriver->clearController(this->panelNumber);

   this->lcdDriver->printf(68, 0, "%02d:%02d:%02d", hours, minutes, seconds);

   this->lcdDriver->flushVM();
}
