#include "lcdClass.h"

void registerDriver(struct lcdDriver *driver, void (*driverRegister)(struct lcdDriver *))
{
	driverRegister(driver);
}
