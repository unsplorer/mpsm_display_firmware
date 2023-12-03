#include <ArduinoOTA.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <TFT.hpp>
#include <WiFiManager.h>
#include <WiFiUdp.h>

TFT tft;
/*
  TODO:
    ADD ENCODER FUNCTIONALITY
    TEST ENCODER PINS
*/
void setupOTA() {
  ArduinoOTA.onStart([]() {});
  ArduinoOTA.onEnd([]() {});
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {});
  ArduinoOTA.onError([](ota_error_t error) {});
  ArduinoOTA.begin();
}

void setup() {
  // E-Z wifi manager. Wifi will be used for OTA updates.
  WiFiManager wifiManager;
  wifiManager.autoConnect();
  setupOTA();
}

void loop() {
  ArduinoOTA.handle();
  yield();
}