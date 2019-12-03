# Rescreen displaying Japanese text

<div align=center><img src="https://raw.githubusercontent.com/ansonhe97/rawimages/master/img/IMG_0121.2019-12-03%2009_33_27.gif"/></div>

## Overview

This example simply demonstrates loading two images in the same time to create visual effects, and to make it more fun, the actual text is variable according to the inboard accelerator and background is fixed.

### Features

- Shaking the Rescreen to check out the effect!

## Arduino libraries needed

- Install the LCD screen library `Seeed_Arduino_LCD`, please visit [TFT LCD Overview](https://github.com/ansonhe97/GroveUIDocs/blob/master/RescreenDocs/TFT%20LCD%20Overview.md) for more information.

- Install the SD Card library `Seeed_Arduino_FS`, Please visit [Seeed-Arduino-FS](https://github.com/Seeed-Studio/Seeed_Arduino_FS/tree/dev) for more information.

- Install the on-board accelerator library `Seeed_Arduino_LIS3DHTR`, Please visit [Seeed_Arduino_LIS3DHTR](https://github.com/Seeed-Studio/Seeed_Arduino_LIS3DHTR) for more information.

- Install the `RawImage.h` library, Please visit [Loading Images](https://github.com/ansonhe97/GroveUIDocs/blob/master/RescreenDocs/loadingImage.md) for more information.

## Arduino Instructions

1. Download the `bg.bmp` and `text.bmp` files, and save them in the SD card.

2. Download the `Japanese_text.ino` and `RawImage.h` file and upload to your Rescreen through `Adruino IDE`. Make sure you installed all the libraries.

3. Start moving your Rescreen and interact!

## Code

- **To initialise the LCD screen**

```Cpp
TFT_eSPI tft;

void setup() {
  ...
    tft.begin();
    tft.setRotation(3);
  ...
}
```

- **To initialise the SD card**

```Cpp
void setup() {
  ...
    if (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI)) {
      while (1);
  }
  ...
}
```

- **To initialise the on-board Accelerator**

```Cpp
LIS3DHTR<TwoWire>  lis;

void setup () {
  ...
  lis.begin(Wire1);
  lis.setOutputDataRate(LIS3DHTR_DATARATE_25HZ); //Output rate of Accelerator
  lis.setFullScaleRange(LIS3DHTR_RANGE_2G); //Scale selection
  ...
}

void loop() {
  ...
  float x_raw = lis.getAccelerationX(); //Read the raw x-axis values of acc
  float y_raw = lis.getAccelerationY(); //Read the raw y-axis values of acc
  ...
}
```

- **To initialise Image and Draw Image**

In this example, two images are needed so they are first loaded into buffer, then push to the LCD screen.

For more information, please visit [Loading Images](https://github.com/ansonhe97/GroveUIDocs/blob/master/RescreenDocs/loadingImage.md).

```Cpp
//initlisitng two 8-bit image
Raw8 * text;
Raw8 * background;

void setup() {
    ...
    //load images from sd card
    text = newImage<uint8_t>("text.bmp");
    background = newImage<uint8_t>("bg.bmp");
}
void loop() {
  ...
    writeToBuffer(0, 0, background); //write backgound to buffer
    writeToBuffer(x_axis, y_axis, text); //write text to buffer
    flushBuffer(); //push to tft lcd screen
    clearBuffer();
}
```

## Complete code

Please visit [Japanese_text](https://github.com/ansonhe97/GroveUIDocs/tree/master/Rescreen%20demo/Japanese_text) to view the complete code.