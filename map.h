#ifndef MAP_H
#define MAP_H

#include <TFT_eSPI.h>
#include "gps.h"
#include "open-street-map.h"

#define DEFAULT_ZOOM 19

class Map {
  private:
    TFT_eSPI *screen;
    int zoom;
    OpenStreetMapTile currentOpenStreetMapTile;
  public:
    Map(TFT_eSPI *screen);
    void setup();
    void loop(GPSPosition position);
};

#endif