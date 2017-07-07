#include "DS1302.h"



void DS1302Init(void)
{
   //pull the io line low
   DS1302_IO_DDR |= (1 << DS1302_IO);
   DS1302_IO_PORT &= ~(1 << DS1302_IO);

   //Configure the reset pin as output
   DS1302_CE_DDR |= (1 << DS1302_CE); 

   //Configure the clock pin as output
   DS1302_CLK_DDR |= (1 << DS1302_CLK);
   //Make sure out clock is low
   DS1302_CLK_PORT &= ~(1 << DS1302_CLK);


   //This concept of reset may not exist
   DS1302Start();
}


//These will need more work as it also sets the seconds
void DS1302Stop(void) 
{
   DS1302WriteByte(0x80, (1 << 7));
}


void DS1302Start(void) 
{
   DS1302WriteByte(0x80, 0x00);
}


//This function assumes pins are set up correctly already for writing 
void DS1302WriteByteClock(unsigned char byte)
{
   for(uint8_t i = 0; i < 8; i ++) 
   {
      if(byte & (1 << i)) 
      {
         DS1302_IO_PORT |= (1 << DS1302_IO);
      }
      //Pull the clock line high
      DS1302_CLK_PORT |= (1 << DS1302_CLK);
      //Wait for the chip to read the byte
      _delay_us(DS1302_CLK_DELAY);

      //Pull the clock line low again
      DS1302_CLK_PORT &= ~(1 << DS1302_CLK);

      //Pull the io pin low (even if it wasn't set high to begin with)
      DS1302_IO_PORT &= ~(1 << DS1302_IO);

      //Give the chip time before the next read
      _delay_us(DS1302_CLK_DELAY);
   }
}
void DS1302WriteByte(unsigned char commandByte, unsigned char byte)
{
   //pull CE/RST high
   DS1302_CE_PORT |= (1 << DS1302_CE);

   //Since we are reading, we set the IO pin to output
   DS1302_IO_DDR |= (1 << DS1302_IO);
   //Make sure the IO port pin is low
   DS1302_IO_PORT &= ~(1 << DS1302_IO);

   //Write the command byte
   DS1302WriteByteClock(commandByte);
   //Write the actualy byte
   DS1302WriteByteClock(byte);

   //pull CE/RST low 
   DS1302_CE_PORT &= ~(1 << DS1302_CE);
}


void DS1302ReadControlClock(void)
{
   //Pull the clock line high
   DS1302_CLK_PORT |= (1 << DS1302_CLK);
   //Wait for the chip to read the byte
   _delay_us(DS1302_CLK_DELAY);


   //Pull the clock line low again
   DS1302_CLK_PORT &= ~(1 << DS1302_CLK);

   //Give the chip time before the next read
   _delay_us(DS1302_CLK_DELAY);
}

//This function assumes pins are set up correctly already for reading
//This one is a bit weird, the chip clocks out the data on the falling edge
//not the rising edge. 
unsigned char DS1302ReadByteClock(void)
{
   unsigned char byte = 0x00;

   for(uint8_t i = 0; i < 8; i ++) 
   {
      if(DS1302_IO_PIN & (1 << DS1302_IO)) 
      {
         byte |= (1 << i);
      }
      DS1302ReadControlClock();
   }
   return byte;
}


unsigned char DS1302ReadByteConsecutive(unsigned char commandByte, uint8_t consecutive)
{
   //Since we are writing first, we set the IO pin to output
   DS1302_IO_DDR |= (1 << DS1302_IO);
   //Make sure the IO port pin is low for input
   DS1302_IO_PORT &= ~(1 << DS1302_IO);
   //pull CE/RST high
   DS1302_CE_PORT |= (1 << DS1302_CE);

   //Write the command byte
   DS1302WriteByteClock(commandByte);

   //Now we are reading, we set the pin to input
   DS1302_IO_DDR &= ~(1 << DS1302_IO);

   unsigned char byte = DS1302ReadByteClock();

   if(!consecutive)
   {
      //pull CE/RST low 
      DS1302_CE_PORT &= ~(1 << DS1302_CE);
   }

   return byte;
}
unsigned char DS1302ReadByte(unsigned char commandByte)
{
   return DS1302ReadByteConsecutive(commandByte, 0);
}



uint8_t DS1302FormatSeconds(unsigned char input) 
{
   uint8_t value = input & 0x0F;
   value += (((input & 0x70) >> 4) * 10);

   return value;
}
uint8_t DS1302ReadSeconds(void)
{
   unsigned char seconds = DS1302ReadByte(0x81);
   return DS1302FormatSeconds(seconds);
}




uint8_t DS1302FormatMinutes(unsigned char input)
{
   uint8_t value = input & 0x0F;
   value += (((input & 0x70) >> 4) * 10);

   return value;
}
uint8_t DS1302ReadMinutes(void)
{
   unsigned char minutes = DS1302ReadByte(0x83);
   return DS1302FormatMinutes(minutes);
}




uint8_t DS1302FormatHours(unsigned char input)
{
   uint8_t value = input & 0x0F;
   value += (((input & 0x30) >> 4) * 10);

   return value;
}
/**
 * Consider puting in some arguments to specify 24 hour ot 12 hour
 */
uint8_t DS1302ReadHours(void)
{
   unsigned char hours = DS1302ReadByte(0x85);
   return DS1302FormatHours(hours);
}



uint8_t DS1302FormatDayOfMonth(unsigned char input)
{
   uint8_t value = input & 0x0F;
   value += (((input & 0x30) >> 4) * 10);

   return value;
}
uint8_t DS1302ReadDayOfMonth(void)
{
   unsigned char dayOfMonth = DS1302ReadByte(0x87);
   return DS1302FormatDayOfMonth(dayOfMonth);
}



uint8_t DS1302FormatMonth(unsigned char input)
{
   uint8_t value = input & 0x0F;
   value += (((input & 0x10) >> 4) * 10);

   return value;
}
uint8_t DS1302ReadMonth(void)
{
   unsigned char month = DS1302ReadByte(0x89);
   return DS1302FormatMonth(month);
}



uint8_t DS1302FormatDayOfWeek(unsigned char input)
{
   uint8_t value = input & 0x07;
   return value;
}
uint8_t DS1302ReadDayOfWeek(void)
{
   unsigned char week = DS1302ReadByte(0x8B);
   return DS1302FormatDayOfWeek(week);
}




uint16_t DS1302FormatYear(unsigned char input)
{
   uint16_t value = input & 0x0F;
   value += (((input & 0xF0) >> 4) * 10);
   value += 2000;

   return value;
}
uint16_t DS1302ReadYear(void)
{
   unsigned char year = DS1302ReadByte(0x8D);
   return DS1302FormatYear(year);
}



uint8_t DS1302FormatWP(unsigned char input)
{
   uint8_t value = input & 0x80;
   return value;
}
uint8_t DS1302ReadWP(void)
{
   unsigned char wb = DS1302ReadByte(0x8F);
   return DS1302FormatWP(wb);
}



struct time DS1302ReadClock(void)
{
   //Send command and read first byte for clock burst mode
   uint8_t seconds = DS1302ReadByteConsecutive(0xBF, 1);

   uint8_t minutes = DS1302ReadByteClock();
   uint8_t hours = DS1302ReadByteClock();
   uint8_t dayOfMonth = DS1302ReadByteClock();
   uint8_t month = DS1302ReadByteClock();
   uint8_t dayOfWeek = DS1302ReadByteClock();
   uint8_t year = DS1302ReadByteClock();
   uint8_t writeProtection = DS1302ReadByteClock();

   //pull CE/RST low 
   DS1302_CE_PORT &= ~(1 << DS1302_CE);

   struct time time;

   time.seconds = DS1302FormatSeconds(seconds);
   time.minutes = DS1302FormatMinutes(minutes);
   time.hours = DS1302FormatHours(hours);
   time.dayOfMonth = DS1302FormatDayOfMonth(dayOfMonth);
   time.month = DS1302FormatMonth(month);
   time.dayOfWeek = DS1302FormatDayOfWeek(dayOfWeek);
   time.year = DS1302FormatYear(year);
   time.wp = DS1302FormatWP(writeProtection);

   return time;

}
















