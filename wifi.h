#ifndef WIFI_H
#define WIFI_H

#include <Arduino.h>

class Wifi {
  public:
    static void setup();
    static void loop();
  private:
    static void connect();
};

#endif