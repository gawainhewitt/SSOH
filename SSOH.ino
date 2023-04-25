/*
An installtion for the NHS

gawainhewitt.co.uk
https://github.com/gawainhewitt
*/

#include "constants.h"
#include "mpr121.h"
#include "reboot.h"
#include "RTClib.h"
#include "playWav.h"

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};



void setup() {
    Wire1.begin();
    Serial.begin(57600);
    init_mpr121();
    setupSound();
    pinMode(rebootButton, INPUT_PULLUP);

    if (! rtc.begin(&Wire1)) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  // When time needs to be re-set on a previously configured device, the
  // following line sets the RTC to the date & time this sketch was compiled
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
}

void loop() {

  currtouched1 = mprBoard_A.touched();

  if(digitalRead(rebootButton) == LOW){
      Serial.print("reboot");
      doReboot();
  }

  for (uint8_t i=0; i < numberOfSensors; i++) {
      if ((currtouched1 & _BV(i)) && !(lasttouched1 & _BV(i)) ) {
      Serial.print(i); Serial.println(" touched of A");
      }
  }

  lasttouched1 = currtouched1;

  DateTime now = rtc.now();

  Serial.print(now.hour(), DEC);
    
  Serial.println();
  
  if(now.hour() > installationStartTime - 1) {
    if(now.hour() < installationEndTime) {
      playFiles();  
    }
  }
}