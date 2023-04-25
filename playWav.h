
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playWav1;       //xy=328,372
AudioEffectFade          fade1;          //xy=509,455
AudioOutputI2S           audioOutput;    //xy=687,423
AudioConnection          patchCord1(playWav1, 0, audioOutput, 0);
AudioConnection          patchCord2(playWav1, 1, fade1, 0);
AudioConnection          patchCord3(fade1, 0, audioOutput, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=911,320
// GUItool: end automatically generated code


#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

void setupSound() {

  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(8);

  // Comment these out if not using the audio adaptor board.
  // This may wait forever if the SDA & SCL pins lack
  // pullup resistors
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.8);
  fade1.fadeOut(10);

  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here, but print a message repetitively
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
}

void playFile(const char *filename)
{
  Serial.print("Playing file: ");
  Serial.println(filename);

  // Start playing the file.  This sketch continues to
  // run while the file plays.
  playWav1.play(filename);

  // A brief delay for the library read WAV info
  delay(25);

  // Simply wait for the file to finish playing.
  // while (playWav1.isPlaying()) {}


}

String tracks[numberOfTracks] = {"LILLIE-ROOM.WAV", "CELESTIAL-LIFT.WAV", "CRAMLINGTON.WAV", "DIFFICULT-FEELINGS.WAV", "DOCTOR.WAV", "EAGLE-WARD.WAV", "CELESTIAL-LIFT2.WAV", "SPIRIT.WAV", "STAIR-PIECE.WAV", "BEING.WAV"};

int currentTrack = 0;

void playFiles() {

  if(!playWav1.isPlaying()){
    byte buffer[tracks[currentTrack].length() + 1];
    tracks[currentTrack].toCharArray(buffer, tracks[currentTrack].length() + 1);
    playFile(buffer);
    if(currentTrack == numberOfTracks - 1){
      currentTrack = 0;
    }else{
      currentTrack += 1;
    }
  }
  // for(int i = 0; i < numberOfTracks; i++){
  //   byte buffer[tracks[i].length() + 1];
  //   tracks[i].toCharArray(buffer, tracks[i].length() + 1);
  //   playFile(buffer);
  //   delay(trackGap);
  // }
}
