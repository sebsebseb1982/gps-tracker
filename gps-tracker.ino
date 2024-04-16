#define USE_LINE_BUFFER
#define TILE_DIMENSION 256

#include <TFT_eSPI.h>       // Hardware-specific library
TFT_eSPI tft = TFT_eSPI();  // Invoke custom library

// Include SPIFFS
#define FS_NO_GLOBALS
#include <FS.h>
#include "SPIFFS.h"  // Required for ESP32 only

#include <HTTPClient.h>

#include "support_functions.h"
#include "screen.h"
#include "wifi.h"

//  int zoom = 14;
int zoom = 18;
int currentXTile = 0;
int currentYTile = 0;

void setup() {
  Serial.begin(115200);
  Wifi::setup();
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(0);

  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS Mount Failed");
    return;
  }
}


void loop() {
  Wifi::loop();
  uint32_t t = millis();

  float latitudeDegrees = 44.806120;
  float longitudeDegrees = -0.584605;
  float latitudeRadians = latitudeDegrees * PI / 180.0;


  int n = pow(2, zoom);
  float xtile = n * ((longitudeDegrees + 180) / 360);
  float ytile = n * (1 - (log(tan(latitudeRadians) + 1 / cos(latitudeRadians)) / PI)) / 2;
  int xTileInt = xtile;
  int yTileInt = ytile;

  if (xTileInt != currentXTile || yTileInt != currentYTile) {

    currentXTile = xTileInt;
    currentYTile = yTileInt;

    for (int xOffset = -1; xOffset <= 1; xOffset++) {
      for (int yOffset = -1; yOffset <= 1; yOffset++) {
        setPngPosition(
          (SCREEN_WIDTH / 2) - (TILE_DIMENSION / 2) + (xOffset * TILE_DIMENSION),
          (SCREEN_HEIGHT / 2) - (TILE_DIMENSION / 2) + (yOffset * TILE_DIMENSION));

        String tileURL;
        tileURL += F("https://tile.openstreetmap.org/");
        tileURL += zoom;
        tileURL += F("/");
        tileURL += xTileInt + xOffset;
        tileURL += F("/");
        tileURL += yTileInt + yOffset;
        tileURL += F(".png");

        load_png(tileURL.c_str());
      }
    }
  }

  int currentPositionX = (SCREEN_WIDTH / 2) - (TILE_DIMENSION / 2)+((xtile - xTileInt) * 256);
  int currentPositionY = (SCREEN_HEIGHT / 2) - (TILE_DIMENSION / 2)+((ytile - yTileInt) * 256);
  Serial.print("n:");
  Serial.println(n);
  Serial.print("xtile:");
  Serial.println(xtile);
  Serial.print("ytile:");
  Serial.println(ytile);
  Serial.print("currentPositionX:");
  Serial.println(currentPositionX);
  Serial.print("currentPositionY:");
  Serial.println(currentPositionY);
  tft.fillCircle(
    currentPositionX,
    currentPositionY,
    2,
    TFT_RED);
  tft.drawCircle(
    currentPositionX,
    currentPositionY,
    5,
    TFT_RED);
}