#include <ArduinoOTA.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <WiFiUdp.h>

#define PUSH_BUTTON         0           // Encoder pushbutton
#define ENCODER_LEFT        5           // FIXME: These maybe backwards, need to test
#define ENDCODE_RIGHT       4           // ^^ 
#define DATA_PIN            13          // MTCK - maybe the engineers have it backwards, or maybe I do! Logic analyzer will tell
#define CLOCK_PIN           14          // MTMS - Master Transmit Master Select - this is normally the data output
#define MTDO                15          // Normally SPI Data Out -> this is connected to LCD pin 12
#define MTDI                12          // Normally SPI Data IN  -> this is conencted to LCD pin 14
#define BIT_ORDER           LSBFIRST    // littleEndian

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

/**@brief pulses a pin for a specific amount of time
 * @param pin gpio to pulse
 * @param length number of microseconds to pulse pin
 * @param type rising pulse of falling
*/
void pulseGPIO(uint8_t pin, uint8_t length, bool type){
  // get pin's current state
  bool state = digitalRead(pin);
  // set line opposite of pulse type
  // might need to add a delay here to let the line settle.
  digitalWrite(pin,!type);
  // pulse the pin
  digitalWrite(pin,type);
  delayMicroseconds(length);
  digitalWrite(pin,!type);
  // return pin to where it was
  digitalWrite(pin,state);
}

/**@brief pulses the update pin to load data into the display
 * @param pin gpio to pulse
*/
void updateDisplay(){

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

  // send the data to the display via parallel, maybe pulse MTDO or MTDI?
  updateDisplay();
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