#include <WiFi.h>
#include "wifi.h"
#include "secrets.h"

void Wifi::connect() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  //Serial.print("Connexion en cours ");
  int retry = 0; 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    retry ++;

    if(retry == 20) {
      ESP.restart();
    }
    //Serial.print(".");
  }
  //Serial.println("");
  //Serial.print("Connecté au WIFI avec l'adresse IP : ");
  //Serial.println(WiFi.localIP());
}

void Wifi::setup() {
  connect();
}

void Wifi::loop() {
  if(WiFi.status() != WL_CONNECTED) {
    connect();
  }
}