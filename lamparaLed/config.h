#ifndef _CONFIG_H
#define _CONFIG_H


#define EEPROM_ADDR_RGB 0

unsigned long configReadValue(byte *r, byte *g, byte *b);
unsigned long configWriteValue(byte r, byte g, byte b);


#endif
