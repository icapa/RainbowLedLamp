#include <Arduino.h>
#include "buttons.h"

#define TWO_SECONDS 100 // 
#define FIVE_SECONDS  250

int BUTTON_R = 4;
int BUTTON_G = 3;
int BUTTON_B = 2;

bool pulseR = false;
bool pulseG = false;
bool pulseB = false;



int pulseR_count = 0;
int pulseG_count = 0;
int pulseB_count = 0;


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

  /* R button */
  statusButtonR = digitalRead(BUTTON_R);
  if (statusButtonR==0){
    delay(20);
    statusButtonR_prev= digitalRead(BUTTON_R);
    if (statusButtonR_prev == statusButtonR){
      pulseR=true;
      pulseR_count++;
      if (pulseR_count==TWO_SECONDS){
        finalButton = PULSED_LONG_R;
      }
      
      if (pulseR_count>FIVE_SECONDS){
        pulseR_count = FIVE_SECONDS+100;
      }
    }
  }else{
    if (pulseR==true){
      if (pulseR_count<= TWO_SECONDS){
        finalButton = PULSED_SINGLE_R;       
      }    
    }
    pulseR=false;
    pulseR_count=0;
  }

  /* G button */

  statusButtonG = digitalRead(BUTTON_G);
  if (statusButtonG==0){
    delay(20);
    statusButtonG_prev= digitalRead(BUTTON_G);
    if (statusButtonG_prev == statusButtonG){
      pulseG=true;
      pulseG_count++;
      if (pulseG_count==TWO_SECONDS){
        finalButton = PULSED_LONG_G;
      }
      if (pulseG_count==FIVE_SECONDS){
        finalButton = PULSED_MAGIC;
      }
      if (pulseG_count>FIVE_SECONDS){
        pulseG_count =FIVE_SECONDS+100;
      }
    }
  }else{
    if (pulseG==true){
      if (pulseG_count<= TWO_SECONDS){
        finalButton = PULSED_SINGLE_G;       
      }    
    }
    pulseG=false;
    pulseG_count=0;
  }

  /* B button */
  statusButtonB = digitalRead(BUTTON_B);
  if (statusButtonB==0){
    delay(20);
    statusButtonB_prev= digitalRead(BUTTON_B);
    if (statusButtonB_prev == statusButtonB){
      pulseB=true;
      pulseB_count++;
      if (pulseB_count==TWO_SECONDS){
        finalButton = PULSED_LONG_B;
      }
      if (pulseB_count>TWO_SECONDS){
        pulseB_count =TWO_SECONDS+100;
      }
    }
  }else{
    if (pulseB==true){
      if (pulseB_count<= TWO_SECONDS){
        finalButton = PULSED_SINGLE_B;       
      }    
    }
    pulseB=false;
    pulseB_count=0;
  }



  return finalButton;
}

