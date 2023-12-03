#include "TFT.hpp"

TFT::TFT() : Adafruit_GFX(D_WIDTH, D_HEIGHT) {}

void TFT::begin() {
  // two pins for the shift registers
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  // implement display init commands
}

void TFT::write_command(uint8_t cmd) {}

void TFT::write_command_data(uint8_t cmd, uint8_t *data, uint8_t lenInBytes) {
  write_command(cmd);

  // write_data(data, lenInBytes);
  for (int i = 0; i < lenInBytes; i++) {
    write_data(data[i]);
  }
}

void TFT::write_data(uint8_t data) {}

void TFT::write_data(uint8_t *data, uint8_t lenInBytes) {}

void TFT::drawPixel(int16_t x, int16_t y, uint16_t color) {
  setAddrWindow(x, y, x, y);
  write_data_rgb(color, 1);
}

void TFT::setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {}
void TFT::write_data_rgb(uint16_t color, uint32_t repeats) {}
void TFT::setRotation(uint8_t m) {}