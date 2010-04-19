#ifndef _I2CMASTER_H
#define _I2CMASTER_H   1

extern void i2c_init(void);
extern void i2c_start();
extern void i2c_stop(void);
extern unsigned char i2c_write(unsigned char data);
extern unsigned char i2c_read(void);
extern void i2c_waitForComplete();
void i2c_setBitRate(uint16_t bitrateKHz);

#endif
