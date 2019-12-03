#ifdef KENDRYTE_K210
#include <SPIClass.h>
#else
#include <SPI.h>
#endif

#include<string.h>
#include "Seeed_FS.h"
#include"LIS3DHTR.h"
#include"TFT_eSPI.h"
#include"RawImage.h"

#define screen_height   240
#define screen_width    320

LIS3DHTR<TwoWire>  lis;
TFT_eSPI tft;

uint8_t raw[screen_height * screen_width];

void writeToBuffer(int x, int y, Raw8 * img) {
  for (int j = y; j < y + img->height(); j++) {
    for (int i = x; i < x + img->width(); i++) {
      raw[j * screen_width + i] = img->get(i - x, j - y);
    }
  }
}


void clearBuffer() {
  memset(raw, 0, sizeof(raw));
}

void flushBuffer() {
  tft.pushImage(0, 0, tft.width(), tft.height(), raw);
}

#define FILLTER_N 20
int filter(int16_t val) {
  int32_t filter_sum = 0;
  for (uint8_t i = 0; i < FILLTER_N; i++) {
    filter_sum += val;
    delay(1);
  }
  return (int)(filter_sum / FILLTER_N);
}


Raw8 * text;
Raw8 * background;

void setup() {

  if (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI, 16000000)) {
    while (1);
  }
  
  tft.begin();
  tft.setRotation(3);

  lis.begin(Wire1);
  lis.setOutputDataRate(LIS3DHTR_DATARATE_25HZ);
  lis.setFullScaleRange(LIS3DHTR_RANGE_2G);

  Serial.begin(115200);
  tft.fillScreen(TFT_WHITE);
  
  text = newImage<uint8_t>("text.bmp");
  background = newImage<uint8_t>("bg.bmp");
}

void loop() {
  float x_raw = lis.getAccelerationX();
  float y_raw = lis.getAccelerationY();
  int16_t x_value = 100 * x_raw;
  int16_t y_value = 100 * y_raw;
  int16_t x_axis = map(filter(x_value), -15, 15, 88, 92); // mapped x-axis
  int16_t y_axis = map(filter(y_value), -15, 15, 88, 92); // mapped y-axis
  delay(30);

  writeToBuffer(0, 0, background);
  writeToBuffer(x_axis, y_axis, text);
  flushBuffer();
  clearBuffer();
}
