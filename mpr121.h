#include <bus1_MPR121.h> // use this modified adafruit library to allow use of other i2c busses - https://github.com/gawainhewitt/bus1_MPR121
// #include "Adafruit_MPR121.h" // alternatively you can use the standard Adafruit library if using bus 0
#include <Wire.h>

Adafruit_MPR121 mprBoard_A = Adafruit_MPR121();

uint16_t lasttouched1 = 0;
uint16_t currtouched1 = 0;

void init_mpr121()
{

    if (!mprBoard_A.begin(0x5A)) {
    Serial.println("MPR121 A not found, check wiring?");
    while (1);
    }
    Serial.println("MPR121 A found!");

    mprBoard_A.writeRegister(MPR121_ECR, 0x00); // stop board
    mprBoard_A.setThreshholds(40, 6);   //set sensitivity - also note spelling mistake
    mprBoard_A.writeRegister(MPR121_FDLF, 0x78);
    mprBoard_A.writeRegister(MPR121_ECR, 0x8F); //start board
}

void checkTouch() {
    currtouched1 = mprBoard_A.touched();

    for (uint8_t i=0; i < numberOfSensors; i++) {
        if ((currtouched1 & _BV(i)) && !(lasttouched1 & _BV(i)) ) {
          Serial.print(i); Serial.println(" touched of A");
          fade1.fadeIn(100);
        }
        if (!(currtouched1 & _BV(i)) && (lasttouched1 & _BV(i)) ) {
          Serial.print(i); Serial.println(" released of A");
          fade1.fadeOut(100);
        }
    }

    lasttouched1 = currtouched1;

}