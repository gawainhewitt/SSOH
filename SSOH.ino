/*
An installtion for the NHS

gawainhewitt.co.uk
https://github.com/gawainhewitt
*/

#include "constants.h"
#include "reboot.h"
#include "realTimeClock.h"
#include "playWav.h"
#include "mpr121.h"

void setup() {
    Wire1.begin();
    Serial.begin(57600);
    init_mpr121();
    setupSound();
    initClock();
    pinMode(rebootButton, INPUT_PULLUP);
}
    
void loop() {

  checkReboot();

  checkTouch();

  DateTime now = rtc.now();

  Serial.println(now.hour(), DEC);
  
  if(now.hour() > installationStartTime - 1) {
    if(now.hour() < installationEndTime) {
      playFiles();  
    }
  }
}