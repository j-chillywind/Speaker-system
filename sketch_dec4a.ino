#include "SD.h"
#define SD_ChipSelectPin 10
#include "TMRpcm.h"
#include "SPI.h"

TMRpcm tmrpcm;
const int switchPin = 2;  // DPDT middle pin connected here

bool isPlaying = false; // Flag to track if the music is currently playing

void setup() {
  tmrpcm.speakerPin = 9;
  pinMode(switchPin, INPUT_PULLUP); // Set the switch pin as input
  Serial.begin(9600);
  
  if (!SD.begin(SD_ChipSelectPin)) {
    Serial.println("SD initialization failed");
    return;
  }
  
  tmrpcm.setVolume(5); // Set initial volume level
}

void loop() {
  // Read the switch state  
  int switchState = digitalRead(switchPin);

  if (switchState == HIGH) {
    // If the switch is ON and music is not already playing, play the music
    if (!isPlaying) {
      tmrpcm.play("test.wav");
      isPlaying = true; // Set the flag to indicate music is playing
      Serial.println("Music ON");
    }
  } else {
    // If the switch is OFF and music is currently playing, stop the music
    if (isPlaying) {
      tmrpcm.stopPlayback();
      isPlaying = false; // Reset the flag
      Serial.println("Music OFF");
    }
  }
  
  delay(100); // Short delay for debounce
}
