#include "DS1302.h"



void DS1302Init(void)
{

   //pull the io line low
   DS1302_IO_DDR |= (1 << DS1302_IO);
   DS1302_IO_PORT &= ~(DS1302_IO);

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
      _delay_ms(DS1302_CLK_DELAY);

      //Pull the clock line low again
      DS1302_CLK_PORT &= ~(1 << DS1302_CLK);

      //Pull the io pin low (even if it wasn't set high to begin with)
      DS1302_IO_PORT &= ~(1 << DS1302_IO);

      //Give the chip time before the next read
      _delay_ms(DS1302_CLK_DELAY);


   }
}
void DS1302WriteByte(unsigned char commandByte, unsigned char byte)
{
   //Set up the command byte with the write flag
   //commandByte &= ~1;
   //commandByte |= (1 << 7);

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


//This function assumes pins are set up correctly already for reading
//This one is a bit weird, the chip clocks out the data on the falling edge
//not the rising edge. 
unsigned char DS1302ReadByteClock(void)
{
   unsigned char byte = 0x00;

   for(uint8_t i = 0; i < 7; i ++) 
   {

      if(DS1302_IO_PIN & (1 << DS1302_IO)) 
      {
         byte |= (1 << i);
      }

      //Pull the clock line high
      DS1302_CLK_PORT |= (1 << DS1302_CLK);
      //Wait for the chip to read the byte
      _delay_ms(DS1302_CLK_DELAY);


      //Pull the clock line low again
      DS1302_CLK_PORT &= ~(1 << DS1302_CLK);

      //Give the chip time before the next read
      _delay_ms(DS1302_CLK_DELAY);
   }
   if(DS1302_IO_PIN & (1 << DS1302_IO)) 
   {
      byte |= (1 << 7);
   }
   return byte;
}

unsigned char DS1302ReadByte(unsigned char commandByte, uint8_t ramOrCk)
{
   //Set up the command byte with the read flag
   //commandByte |= 1;
   //commandByte |= (1 << 7);
   if(ramOrCk) 
   {
      commandByte |= (1 << DS1302_RAM_CK_BIT);
   }

   //pull CE/RST high
   DS1302_CE_PORT |= (1 << DS1302_CE);

   //Since we are reading, we set the IO pin to output
   DS1302_IO_DDR |= (1 << DS1302_IO);
   //Make sure the IO port pin is low
   DS1302_IO_PORT &= ~(1 << DS1302_IO);

   //Write the command byte
   DS1302WriteByteClock(commandByte);

   unsigned char byte = DS1302ReadByteClock();

   //pull CE/RST low 
   DS1302_CE_PORT &= ~(1 << DS1302_CE);

   return byte;
}

uint8_t DS1302ReadSeconds(void)
{
   unsigned char seconds = DS1302ReadByte(0x81, DS1302_CK);
   uint8_t value = seconds & 0x0F;
   value += (((seconds & 0x70) >> 4) * 10);

   return value;
}

uint8_t DS1302ReadMinutes(void)
{
   unsigned char minutes = DS1302ReadByte(0x83, DS1302_CK);
   uint8_t value = minutes & 0x0F;
   value += (((minutes & 0x70) >> 4) * 10);

   return value;
}

uint8_t DS1302ReadHours()
{
   unsigned char hours = DS1302ReadByte(0x85, DS1302_CK);
   uint8_t value = hours & 0x0F;
   value += (((hours & 0x30) >> 4) * 10);

   return value;
}
















