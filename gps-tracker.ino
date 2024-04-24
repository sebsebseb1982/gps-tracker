#include <TFT_eSPI.h>       // Hardware-specific library
TFT_eSPI tft = TFT_eSPI();  // Invoke custom library

// Include SPIFFS
#define FS_NO_GLOBALS
#include <FS.h>
#include "SPIFFS.h"  // Required for ESP32 only

#include "screen.h"
#include "wifi.h"
#include "gps.h"
#include "open-street-map.h"
#include "map.h"
#include "buzzer.h"

Screen screen = Screen(&tft);
Map myMap = Map(&tft);
GPS gps = GPS();

void setup() {
  Serial.begin(115200);
  Buzzer::setup();
  Buzzer::off();
  Wifi::setup();
  screen.setup();

  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS Mount Failed");
    return;
  }
  gps.setup();
  myMap.setup();
}

void loop() {
  Wifi::loop();
  gps.loop();
  screen.loop();

  if (gps.ready) {
    myMap.loop(gps.currentPosition);
  }
}