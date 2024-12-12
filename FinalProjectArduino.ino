#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

#define SHIELD_RESET  -1
#define SHIELD_CS     7
#define SHIELD_DCS    6
#define CARDCS        4
#define DREQ          3

#define BUTTON_PIN    9
#define LED_PIN       11

Adafruit_VS1053_FilePlayer musicPlayer =  Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  if (!musicPlayer.begin()) {
    Serial.println("VS1053 not found");
    while (1);
  }
  if (!SD.begin(CARDCS)) {
    Serial.println("SD card failed");
    while (1);
  }
  musicPlayer.setVolume(1, 1);
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);
  playTrack("/track001.mp3");
}

void loop() {
  int time_past = millis();
  while(millis() - time_past < 5*60*1000)
  {
    int buttonState = digitalRead(BUTTON_PIN) == LOW ? 1 : 0;
    Serial.println(buttonState);
    digitalWrite(LED_PIN, buttonState == 1 ? LOW : HIGH);
    // delay(100); 
  } 
  playTrack("/track001.mp3"); 

}

void playTrack(const char* trackName) {
  Serial.print("Playing ");
  Serial.println(trackName);
  musicPlayer.startPlayingFile(trackName);
}
