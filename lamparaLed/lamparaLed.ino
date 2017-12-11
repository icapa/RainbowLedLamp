#include <WS2812.h>

#define NUM_LED 60

#define BOTON_R 2
#define BOTON_G 3
#define BOTON_B 4

WS2812 LED(NUM_LED);
cRGB value;
byte tono=0;
int up=1;
int numLed;



void setup() {
  

  
  LED.setOutput(7);
  delay(100);
  todos(0,0,0);
}

void loop() {

    delay(100);
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


  
  

