#include <arduino.h>
#include "open-street-map.h"

OpenStreetMapTile::OpenStreetMapTile() {
}

OpenStreetMapTile::OpenStreetMapTile(float x, float y, int zoom) {
  this->x = x;
  this->y = y;
  this->zoom = zoom;
}

int OpenStreetMapTile::getXIntegerPart() {
  return (int)this->x;
}

int OpenStreetMapTile::getYIntegerPart() {
  return (int)this->y;
}

float OpenStreetMapTile::getXFractionalPart() {
  return this->x - getXIntegerPart();
}

float OpenStreetMapTile::getYFractionalPart() {
  return this->y - getYIntegerPart();
}

boolean OpenStreetMapTile::sameTile(OpenStreetMapTile anotherOpenStreetMapTile) {
  return this->getXIntegerPart() == anotherOpenStreetMapTile.getXIntegerPart()
    && this->getYIntegerPart() == anotherOpenStreetMapTile.getYIntegerPart();
}

OpenStreetMapTile OpenStreetMap::getOpenStreetMapTileFromPosition(GPSPosition gpsPosition, int zoom) {
  int n = pow(2, zoom);
  float xTile = n * ((gpsPosition.getLongitudeInDegrees() + 180) / 360);
  float yTile = n * (1 - (log(tan(gpsPosition.getLatitudeInRadians()) + 1 / cos(gpsPosition.getLatitudeInRadians())) / PI)) / 2;

  return OpenStreetMapTile(
    xTile,
    yTile,
    zoom);
}