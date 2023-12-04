#include <ArduinoOTA.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <TFT.h>
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
  tft.begin();

  // E-Z wifi manager. Wifi will be used for OTA updates.
  WiFiManager wifiManager;
  wifiManager.autoConnect();
  setupOTA();

  tft.printf("Connected\nSSID:\t%s\nIP:\t%s\n",WiFi.SSID(),WiFi.localIP());
}

void loop() {
  ArduinoOTA.handle();
  yield();
}