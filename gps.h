#ifndef GPS_H
#define GPS_H
#include <TinyGPSPlus.h>

class GPSPosition {
  private:
    float latitudeInDegrees;
    float longitudeInDegrees;
  public:
    GPSPosition();
    GPSPosition(float latitudeInDegrees, float longitudeInDegrees);
    float getLatitudeInDegrees();
    float getLongitudeInDegrees();
    float getLatitudeInRadians();
    float getLongitudeInRadians();
    void setup();
    void loop();
};

class GPS {
  private:
    TinyGPSPlus gps;
  public:
    GPS();
    GPSPosition currentPosition;
    bool ready;
    void setup();
    void loop();
};

#endif