#include "image.h"

void loadImage(struct httpd_fs_file *file)
{
	char blah[10];
	//eeprom_write_block((void *)0x0000, "hello", 6);
	eeprom_read_block(blah, (void *)0x0000, 6);
	writeLnLen(blah, 6);

	//char *image = malloc(441);
	//eeprom_read_block(image, (void *)0x000, 441);
	//writeLnLen(image, 441);
	//file->data = image;
	//file->len = 441;
}
