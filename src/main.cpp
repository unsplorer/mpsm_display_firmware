#include <ArduinoOTA.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <WiFiUdp.h>

#define DATA_PIN            13          // MTCK - maybe the engineers have it backwards, or maybe I do! Logic analyzer will tell
#define CLOCK_PIN           14          // MTMS - Master Transmit Master Select - this is normally the data output
#define MTDO                15          // Normally SPI Data Out -> this is connected to LCD pin 12
#define MTDI                12          // Normally SPI Data IN  -> this is conencted to LCD pin 14
#define BIT_ORDER           LSBFIRST    // littleEndian

void setupOTA() {
  ArduinoOTA.onStart([]() {});
  ArduinoOTA.onEnd([]() {});
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {});
  ArduinoOTA.onError([](ota_error_t error) {});
  ArduinoOTA.begin();
}

/**@brief sends 16 bits to the 2 shift registers
 * @param data the data to send
*/
void sendDisplayData(uint16_t data) {
  // we're guessing that the display operates with a 16bit parallel bus.
  // the esp8266ex is driving the display with 2 74hc164d shift registers
  // and maybe the hardware SPI bus
  shiftOut(DATA_PIN, CLOCK_PIN, BIT_ORDER, (data << 8));
  // now the second
  shiftOut(DATA_PIN, CLOCK_PIN, BIT_ORDER, (data));
}

void setup() {
  // two pins for the shift registers
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);

  // E-Z wifi manager. Wifi will be used for OTA updates.
  WiFiManager wifiManager;
  wifiManager.autoConnect();
  setupOTA();
}

void loop() {
  ArduinoOTA.handle();
  yield();
}