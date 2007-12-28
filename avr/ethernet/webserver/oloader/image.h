#include <avr/eeprom.h>
#include <stdlib.h>
#include <string.h>
#include "../httpd-fs.h"

#ifndef IMAGE_H
#define IMAGE_H

void loadImage(struct httpd_fs_file *file);

#endif
