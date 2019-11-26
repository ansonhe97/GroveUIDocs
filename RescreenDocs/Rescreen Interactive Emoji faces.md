# Rescreen Interactive Emoji faces

<div align=center><img src="https://raw.githubusercontent.com/ansonhe97/rawimages/master/img/C0274.2019-11-26%2014_50_05.gif"/></div>

## Overview

This example demonstrates how to display multiple images (eyes) onto the LCD screen through SD card (BMP format),  and with the use of the built-in buttons and  gyroscope to interact with users.

### Features

- Left-Button: Previous Image (eyes)

- Middle-Button: Animations

- Right-Button: Next Image (eyes)

- Gyro: Eyes moving according to the board orientation

## Arduino libraries needed

- Install the LCD screen library `Seeed_Arduino_LCD-master`, please visit [TFT LCD Overview](https://github.com/ansonhe97/GroveUIDocs/blob/master/RescreenDocs/TFT%20LCD%20Overview.md) for more information.

- Install the SD Card library `Seeed_Arduino_FS-dev`, Please visit [Seeed-Arduino-FS](https://github.com/Seeed-Studio/Seeed_Arduino_FS/tree/dev) for more information.

- Install the on-board accelerator library `Seeed_Arduino_LIS3DHTR-master`, Please visit [Seeed_Arduino_LIS3DHTR](https://github.com/Seeed-Studio/Seeed_Arduino_LIS3DHTR) for more information.

- Install the `RawImage.h` library, Please visit [Loading Images](https://github.com/ansonhe97/GroveUIDocs/blob/master/RescreenDocs/loadingImage.md) for more information.

## Arduino Instructions

1. Download the `face` file (including all the images), and save them in the SD card.

2. Download the `Emoji_face.ino` and `RawImage.h` file and upload to your Rescreen through `Adruino IDE`. Make sure you installed all the libraries.

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

- **To initialise the built-in Button**

```Cpp
void setup() {
  ...
  pinMode(BUTTON_1, INPUT); //left button
  pinMode(BUTTON_2, INPUT); //middle button
  pinMode(BUTTON_3, INPUT); //right button
  ...
}
```

- **To initialise Image and Draw Image**

In this example, the images are not 320x240 full-size so when drawing, need to specified where the image begins. The images are first loaded into the buffer to avoid image lagging from shaking the rescreen.

For more information, please visit [Loading Images](https://github.com/ansonhe97/GroveUIDocs/blob/master/RescreenDocs/loadingImage.md).

```Cpp
void loop() {
  ...
  Raw8 * eyes = newImage<uint8_t>(eye[eye_count]); //initilising 8-bit images
  writeToBuffer(x_axis, y_axis, eyes); //writing to buffer first, see full code to check this function
  ...
}
```
