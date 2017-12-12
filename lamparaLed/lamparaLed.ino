#include <WS2812.h>
#include "buttons.h"
#include "config.h"
#include "EEPROM.h"

#define BAUDRATE 9600

#define NUM_LED 60
#define MAX_POWER 250

WS2812 LED(NUM_LED);
cRGB value;
byte r=0;
byte g=0;
byte b=0;

int numLed;

int buttonPulse=0;
bool updateLeds = false;

bool magicMode=false;

void setup() {
  
  
  /* Input buttons */
  configure_buttons();
  
  LED.setOutput(7);
  delay(100);
  todos(0,0,0);
  Serial.begin(BAUDRATE);
  while(!Serial);
  Serial.write("Connect\r\n");
  configReadValue(&r,&g,&b);
  Serial.println("Values from eeprom:");
  Serial.println(r,DEC);
  Serial.println(g,DEC);
  Serial.println(b,DEC);

  Serial.println("PROBANDO...");


  


  if (r!=0xFF && g!=0xFF && b!=0xFF){
    todos(r,g,b);
  }
  
}

void loop() {
  buttonPulse = button_loop();
  
  if (buttonPulse == PULSED_SINGLE_R){
    if (r>MAX_POWER){
      r = 0;
    }
    else if (r==MAX_POWER-10){
      todos(255,0,0);
      delay(1000);
      todos(0,0,0);
      delay(1000);
      Serial.println("Red max");
      r= 255;
    }
    else{
      r = r + 10;
    }
    updateLeds=true;
  }

  
  if (buttonPulse == PULSED_SINGLE_G){
    if (g>MAX_POWER){
      g = 0;
    }
    else if (g==MAX_POWER-10){
      todos(0,255,0);
      delay(1000);
      todos(0,0,0);
      delay(1000);
      Serial.println("Green max");
      g = 255;
    }
    else{
      g = g + 10;
    }
    updateLeds=true;
  }
  
  if (buttonPulse == PULSED_SINGLE_B){
    if (b>MAX_POWER){
      b = 0;
    }
    else if (b==MAX_POWER-10){
      Serial.println("Blue max");
      todos(0,0,255);
      delay(1000);
      todos(0,0,0);
      delay(1000);
      
      b = 255;
    }
    else{
      b = b + 10;
    }
    updateLeds=true;
    
  }

  
  if (buttonPulse == PULSED_LONG_R){
    if (r!=0 || g!=0 || b!=0){
      r=0;
      g=0;
      b=0;
    }
    updateLeds=true;
  }
  if (buttonPulse == PULSED_LONG_B){
    Serial.println("Save rgb values...");
    Serial.println(configWriteValue(r,g,b),HEX);
    
  }

  if (buttonPulse == PULSED_LONG_G){
    Serial.println(configReadValue(&r,&g,&b),HEX);
    Serial.println("Values from eeprom:");
    Serial.println(r,DEC);
    Serial.println(g,DEC);
    Serial.println(b,DEC);
    updateLeds=true;
    
  }
  
  if (buttonPulse == PULSED_MAGIC){
    magicMode = !magicMode;
    if (magicMode==true){
       doMagic();
      Serial.println("Magic!!!!");
    }
    else{
      configReadValue(&r,&g,&b);
      updateLeds=true;
      Serial.println("Magic END...!!!");
    }
  }


  

  if (updateLeds==true){
    updateLeds=false;
    todos(r,g,b);
    /*
    Serial.println("RGB:");
    Serial.println(r,DEC);
    Serial.println(g,DEC);
    Serial.println(b,DEC);
    */
    
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

void doMagic(){
  int rest;
  value.b=b;value.g=g;value.r=r;
  for (int numLed=0;numLed<NUM_LED;numLed++)
  { 
    rest = numLed%3;
    if (rest==0){ 
      value.r=255;
      value.g=0;
      value.b=0;
    }else if (rest==1){
      value.r=0;
      value.g=255;
      value.b=0;
    }
    else if (rest==2){
      value.r=0;
      value.g=0;
      value.b=255;
    }
    LED.set_crgb_at(numLed,value);
  } 
  LED.sync();
}

  
  

