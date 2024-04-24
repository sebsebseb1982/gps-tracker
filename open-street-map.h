#ifndef OPEN_STREET_MAP_H
#define OPEN_STREET_MAP_H

#include "gps.h"

#define TILE_DIMENSION 256

class OpenStreetMapTile {
  private:
    float x;
    float y;
    int zoom;
  public:
    OpenStreetMapTile();
    OpenStreetMapTile(float x, float y, int zoom);
    int getXIntegerPart();
    int getYIntegerPart();
    float getXFractionalPart();
    float getYFractionalPart();
    boolean sameTile(OpenStreetMapTile anotherOpenStreetMapTile);
};

class OpenStreetMap {
  public:
    static OpenStreetMapTile getOpenStreetMapTileFromPosition(GPSPosition gpsPosition, int zoom);
};

#endif