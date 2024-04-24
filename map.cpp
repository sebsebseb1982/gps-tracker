#include "map.h"
#include "support_functions.h"
#include "screen.h"

Map::Map(TFT_eSPI *screen) {
  this->screen = screen;
  this->zoom = DEFAULT_ZOOM;
  this->currentOpenStreetMapTile = OpenStreetMapTile(0.0, 0.0, this->zoom);
}

void Map::setup() {
}

void Map::loop(GPSPosition position) {
  OpenStreetMapTile openStreetMapTile = OpenStreetMap::getOpenStreetMapTileFromPosition(position, this->zoom);
  Serial.println("Map::loop()");
  if (!openStreetMapTile.sameTile(this->currentOpenStreetMapTile)) {
    currentOpenStreetMapTile = openStreetMapTile;

    for (int xOffset = -1; xOffset <= 1; xOffset++) {
      for (int yOffset = -1; yOffset <= 1; yOffset++) {
        int pngPositionX = (SCREEN_WIDTH / 2) - (TILE_DIMENSION / 2) + (xOffset * TILE_DIMENSION);
        int pngPositionY = (SCREEN_HEIGHT / 2) - (TILE_DIMENSION / 2) + (yOffset * TILE_DIMENSION);
        setPngPosition(
          pngPositionX,
          pngPositionY,
           this->screen
        );

        String tileURL;
        tileURL += F("https://tile.openstreetmap.org/");
        tileURL += this->zoom;
        tileURL += F("/");
        tileURL += openStreetMapTile.getXIntegerPart() + xOffset;
        tileURL += F("/");
        tileURL += openStreetMapTile.getYIntegerPart() + yOffset;
        tileURL += F(".png");

        load_png(tileURL.c_str());
      }
    }
  }

  int currentPositionX = (SCREEN_WIDTH / 2) - (TILE_DIMENSION / 2) + (openStreetMapTile.getXFractionalPart() * 256);
  int currentPositionY = (SCREEN_HEIGHT / 2) - (TILE_DIMENSION / 2) + (openStreetMapTile.getYFractionalPart() * 256);

  this->screen->drawPixel(
    currentPositionX,
    currentPositionY,
    TFT_RED);
}