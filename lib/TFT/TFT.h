// Display.h

#define D_WIDTH 480
#define D_HEIGHT 320

#include <Adafruit_GFX.h>
#include <ESP8266WiFi.h>
#include <pins.h>

class TFT : public Adafruit_GFX {

private:
  void write_command(uint8_t cmd);
  void write_command_data(uint8_t cmd, uint8_t *data, uint8_t lenInBytes);
  void write_data(uint8_t data);
  void write_data(uint8_t *data, uint8_t lenInBytes);
  void write_data_rgb(uint16_t color, uint32_t repeats);
  void setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
  
public:
  TFT();

  void begin();

  void drawPixel(int16_t x, int16_t y, uint16_t color);

  void setRotation(uint8_t m);
};
