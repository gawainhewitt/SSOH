/*
An installtion for the NHS

gawainhewitt.co.uk
https://github.com/gawainhewitt
*/

#include "constants.h"
#include "mpr121.h"
#include "reboot.h"

void setup() {
    Serial.begin(9600);
    init_mpr121();
    pinMode(rebootButton, INPUT_PULLUP);
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

  return;

    // debugging info, what
  Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); Serial.println(mprBoard_A.touched(), HEX);
  Serial.print("Filt: ");
  for (uint8_t i=0; i<12; i++) {
    Serial.print(mprBoard_A.filteredData(i)); Serial.print("\t");
  }
  Serial.println();
  Serial.print("Base: ");
  for (uint8_t i=0; i<12; i++) {
    Serial.print(mprBoard_A.baselineData(i)); Serial.print("\t");
  }
  Serial.println();
  
  // put a delay so it isn't overwhelming
  delay(100);
}