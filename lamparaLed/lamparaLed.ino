#include <WS2812.h>
#include "buttons.h"

#define BAUDRATE 9600

#define NUM_LED 60
#define MAX_POWER 100

WS2812 LED(NUM_LED);
cRGB value;
byte r=0;
byte g=0;
byte b=0;

int numLed;

int buttonPulse=0;
bool updateLeds = false;

void setup() {
  
  
  /* Input buttons */
  configure_buttons();
  
  LED.setOutput(7);
  delay(100);
  todos(0,0,0);
  Serial.begin(BAUDRATE);
  while(!Serial);
  Serial.write("Connect\r\n");
}

void loop() {
  buttonPulse = button_loop();
  if (buttonPulse == PULSED_SINGLE_R){
    r = r + 10;
    if (r>MAX_POWER) r = 0;
    updateLeds=true;
  }
  if (buttonPulse == PULSED_SINGLE_G){
    g = g + 10;
    if (g>MAX_POWER) g = 0;
    updateLeds=true;
  }
  if (buttonPulse == PULSED_SINGLE_B){
    b = b + 10;
    if (b>MAX_POWER) b = 0;
    updateLeds=true;
  }

  if (updateLeds==true){
    updateLeds=false;
    todos(r,g,b);
    Serial.println("RGB:");
    Serial.println(r,DEC);
    Serial.println(g,DEC);
    Serial.println(b,DEC);
  }
  
  delay(5);
}

void todos(byte r, byte g, byte b)
{
  value.b=b;value.g=g;value.r=r;
  for (int numLed=0;numLed<NUM_LED;numLed++)
  {  
    LED.set_crgb_at(numLed,value);
  } 
  LED.sync();
}


  
  

