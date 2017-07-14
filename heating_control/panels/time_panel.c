#include "time_panel.h"



void drawTimePanel(struct timePanel *this) 
{
   struct time time;
   time = DS1302ReadClock();

   this->lcdDriver->clearController(this->panelNumber);

   char month[4];
   getMonth(time.month, month);
   char dayOfWeek[4];
   getDayOfWeek(time.dayOfWeek, dayOfWeek);

   this->lcdDriver->printf(68, 0, "%02d:%02d:%02d", time.hours, time.minutes, time.seconds);
   this->lcdDriver->printf(68, 8, "%s %d %s", dayOfWeek, time.dayOfMonth, month);
   this->lcdDriver->printf(68, 16, "%d", time.year);

   this->lcdDriver->flushVM();
}

