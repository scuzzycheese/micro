#include "time_panel.h"



void drawTimePanel(struct timePanel *this) 
{
   uint8_t seconds = DS1302ReadSeconds();
   uint8_t minutes = DS1302ReadMinutes();
   uint8_t hours = DS1302ReadHours();


   uint8_t dayOfMonth = DS1302ReadDayOfMonth();
   uint8_t month = DS1302ReadMonth();
   uint8_t dayOfWeek = DS1302ReadDayOfWeek();
   uint8_t year = DS1302ReadYear();
   uint8_t wb = DS1302ReadWP();


   this->lcdDriver->clearController(this->panelNumber);

   this->lcdDriver->printf(68, 0, "%02d:%02d:%02d", hours, minutes, seconds);
   this->lcdDriver->printf(68, 8, "w:%d d:%d m:%d", dayOfWeek, dayOfMonth, month);
   this->lcdDriver->printf(68, 16, "y:%d wb:%d", year, wb);



   struct time time;
   time = DS1302ReadClock();
   this->lcdDriver->printf(68, 32, "%02d:%02d:%02d", time.hours, time.minutes, time.seconds);
   this->lcdDriver->printf(68, 40, "w:%d d:%d m:%d", time.dayOfWeek, time.dayOfMonth, time.month);
   this->lcdDriver->printf(68, 48, "y:%d wb:%d", time.year, time.wp);


   this->lcdDriver->flushVM();
}
