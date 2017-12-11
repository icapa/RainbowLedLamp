#include "Arduino.h"
#include "EEPROM.h"
#include "config.h"


unsigned long configReadValue(byte *r, byte *g, byte *b){
  unsigned long rgb = 0xFFFFFFFF;
  
  EEPROM.get(0,rgb);

  *r = (rgb>>24) & 0xFF;
  *g = (rgb>>16) & 0xFF;
  *b = (rgb>>8) & 0xFF;
  return rgb;
}
unsigned long configWriteValue(byte r, byte g, byte b){
  unsigned long rgb=0x000000FF;
  rgb = ((unsigned long)r<<24);
  rgb = rgb | ((unsigned long)g<<16);
  rgb = rgb | ((unsigned long)b<<8);
  
  
  EEPROM.put(0,rgb);
  
  return rgb;
}

