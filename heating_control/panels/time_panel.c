#include "time_panel.h"



void drawTimePanel(struct timePanel *this) 
{
   unsigned char readSecondsCommandByte = (0x81);
   unsigned char seconds = DS1302ReadByte(readSecondsCommandByte, DS1302_CK);
   uint8_t value = seconds & 0x0F;
   value += (((seconds & 0x70) >> 4) * 10);



   this->lcdDriver->clearController(this->panelNumber);

   this->lcdDriver->printf(68, 0, "value: %d", value);

   this->lcdDriver->flushVM();
}
