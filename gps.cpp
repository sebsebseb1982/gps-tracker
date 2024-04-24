#include <arduino.h>
#include "gps.h"

GPSPosition::GPSPosition() {
}

GPSPosition::GPSPosition(float latitudeInDegrees, float longitudeInDegrees) {
  this->latitudeInDegrees = latitudeInDegrees;
  this->longitudeInDegrees = longitudeInDegrees;
}

float GPSPosition::getLatitudeInDegrees() {
  return this->latitudeInDegrees;
}

float GPSPosition::getLongitudeInDegrees() {
  return this->longitudeInDegrees;
}

float GPSPosition::getLatitudeInRadians() {
  return this->latitudeInDegrees * PI / 180.0;
}

float GPSPosition::getLongitudeInRadians() {
  return this->longitudeInDegrees * PI / 180.0;
}

GPS::GPS(){
  this->ready = false;
}

void GPS::setup() {
  Serial2.begin(9600, SERIAL_8N1, 0, 4);
}

void GPS::loop() {
  if (Serial2.available() > 0) {
    if (this->gps.encode(Serial2.read())) {
      if (this->gps.location.isValid()) {
        this->ready = true;
        this->currentPosition = GPSPosition(gps.location.lat(), gps.location.lng());
        Serial.print(F("- latitude: "));
        Serial.println(this->gps.location.lat());

        Serial.print(F("- longitude: "));
        Serial.println(this->gps.location.lng());

        Serial.print(F("- altitude: "));
        if (this->gps.altitude.isValid())
          Serial.println(this->gps.altitude.meters());
        else
          Serial.println(F("INVALID"));
      } else {
        Serial.println(F("- location: INVALID"));
      }

      Serial.print(F("- speed: "));
      if (this->gps.speed.isValid()) {
        Serial.print(this->gps.speed.kmph());
        Serial.println(F(" km/h"));
      } else {
        Serial.println(F("INVALID"));
      }

      Serial.print(F("- GPS date&time: "));
      if (this->gps.date.isValid() && this->gps.time.isValid()) {
        Serial.print(this->gps.date.year());
        Serial.print(F("-"));
        Serial.print(this->gps.date.month());
        Serial.print(F("-"));
        Serial.print(this->gps.date.day());
        Serial.print(F(" "));
        Serial.print(this->gps.time.hour());
        Serial.print(F(":"));
        Serial.print(this->gps.time.minute());
        Serial.print(F(":"));
        Serial.println(this->gps.time.second());
      } else {
        Serial.println(F("INVALID"));
      }

      Serial.println();
    }
  }

  if (millis() > 5000 && this->gps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));
    
}