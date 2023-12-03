#include <ArduinoOTA.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <WiFiUdp.h>

#define DATA_PIN 13
#define CLOCK_PIN 14
#define BIT_ORDER LSBFIRST // littleEndian

void setupOTA() {
  ArduinoOTA.onStart([]() {});
  ArduinoOTA.onEnd([]() {});
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {});
  ArduinoOTA.onError([](ota_error_t error) {});
  ArduinoOTA.begin();
}

void sendDisplayData(uint16_t data) {
  // shift out first byte
  shiftOut(DATA_PIN, CLOCK_PIN, BIT_ORDER, (data << 8));
  // now the second
  shiftOut(DATA_PIN, CLOCK_PIN, BIT_ORDER, (data));
}

void setup() {
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);

  WiFiManager wifiManager;
  wifiManager.autoConnect();
  setupOTA();
}

void loop() {
  ArduinoOTA.handle();
  yield();
}