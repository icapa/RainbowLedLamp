#include <Arduino.h>
#include "buttons.h"


int BUTTON_R = 4;
int BUTTON_G = 3;
int BUTTON_B = 2;

bool pulseR = false;
bool pulseG = false;
bool pulseB = false;

bool pulseR_long = false;
bool pulseG_long = false;
bool pulseB_long = false;


int statusButtonR = 0;
int statusButtonG = 0;
int statusButtonB = 0;

int statusButtonR_prev = 0;
int statusButtonG_prev = 0;
int statusButtonB_prev = 0;


void configure_buttons(){
  pinMode(BUTTON_R,INPUT_PULLUP);
  pinMode(BUTTON_G,INPUT_PULLUP);
  pinMode(BUTTON_B,INPUT_PULLUP);
  statusButtonR = digitalRead(BUTTON_R);
  statusButtonR_prev = statusButtonR;
  statusButtonG = digitalRead(BUTTON_G);
  statusButtonG_prev = statusButtonG;
  statusButtonB = digitalRead(BUTTON_B);
  statusButtonB_prev = statusButtonB;
}

  
int button_loop()
{
  int finalButton = 0;
  statusButtonR = digitalRead(BUTTON_R);
  if (statusButtonR != statusButtonR_prev && statusButtonR==0){
    delay(20);
    if (statusButtonR==0){
      finalButton = PULSED_SINGLE_R;
      goto final_return;
    }
  }
  statusButtonG = digitalRead(BUTTON_G);
  if (statusButtonG != statusButtonG_prev && statusButtonG==0){
    delay(20);
    if (statusButtonG==0){
      finalButton = PULSED_SINGLE_G;
      goto final_return;
    }
  }
  statusButtonB = digitalRead(BUTTON_B);
  if (statusButtonB != statusButtonB_prev && statusButtonB==0){
    delay(20);
    if (statusButtonB==0){
      finalButton = PULSED_SINGLE_B;
      goto final_return;
    }
  }
  
final_return:
  statusButtonR_prev = statusButtonR;
  statusButtonG_prev = statusButtonG;
  statusButtonB_prev = statusButtonB;
  
  return finalButton;
}

