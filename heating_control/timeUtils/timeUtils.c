#include "timeUtils/timeUtils.h"


void getMonth(uint8_t month, char *buf)
{
   switch(month)
   {
      case 1: 
      {
         sprintf(buf, "Jan");
         break;
      }
      case 2: 
      {
         sprintf(buf, "Feb");
         break;
      }
      case 3: 
      {
         sprintf(buf, "Mar");
         break;
      }
      case 4: 
      {
         sprintf(buf, "Apr");
         break;
      }
      case 5: 
      {
         sprintf(buf, "May");
         break;
      }
      case 6: 
      {
         sprintf(buf, "Jun");
         break;
      }
      case 7: 
      {
         sprintf(buf, "Jul");
         break;
      }
      case 8: 
      {
         sprintf(buf, "Aug");
         break;
      }
      case 9: 
      {
         sprintf(buf, "Sep");
         break;
      }
      case 10: 
      {
         sprintf(buf, "Oct");
         break;
      }
      case 11: 
      {
         sprintf(buf, "Nov");
         break;
      }
      case 12: 
      {
         sprintf(buf, "Dec");
         break;
      }
   }
}


void getDayOfWeek(uint8_t dayOfWeek, char *buf)
{
   switch(dayOfWeek)
   {
      case 1:
      {
         sprintf(buf, "Mon");
         break;
      }
      case 2:
      {
         sprintf(buf, "Tue");
         break;
      }
      case 3:
      {
         sprintf(buf, "Wed");
         break;
      }
      case 4:
      {
         sprintf(buf, "Thu");
         break;
      }
      case 5:
      {
         sprintf(buf, "Fri");
         break;
      }
      case 6:
      {
         sprintf(buf, "Sat");
         break;
      }
      case 7:
      {
         sprintf(buf, "Sun");
         break;
      }
   }
}
