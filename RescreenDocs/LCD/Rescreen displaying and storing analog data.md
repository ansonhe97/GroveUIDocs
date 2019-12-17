# Rescreen displaying and storing analog data

<div align=center><img src="https://raw.githubusercontent.com/ansonhe97/rawimages/master/img/C0282.2019-11-28%2018_28_03.gif"/></div>

## Overview

This example demonstrates using the line graph functions to display the Grove - Light sensor reading on Rescreen, just like the Serial Plotter! To add more, the light sensor data are stored in the SD Card.

### Features

- Reading Light sensor values and plotting into a line graph

## Arduino libraries needed

- Install the Line Chart library `rescreen_graphics`, please visit [Line Charts](https://github.com/ansonhe97/GroveUIDocs/blob/master/RescreenDocs/linecharts.md) for more information.

- Install the SD Library, please visit [FS](https://github.com/ansonhe97/GroveUIDocs/tree/master/RescreenDocs/FS) for more information.

## Arduino Instructions

1. It is highly recommended to read through [Line Charts](https://github.com/ansonhe97/GroveUIDocs/blob/master/RescreenDocs/linecharts.md) first and before trying out this example code.

2. Download the `AcceratorReadings.ino` file and upload to your Rescreen through `Adruino IDE`. Make sure you installed all the libraries.

3. Change the brightness of surroundings and see the changes in the linegraph!

4. The analog reading can be found in the SD Card in `Readings.txt`

## Code

- **To intialise LCD and Analog port**

<div align=center><img width=333 src="https://raw.githubusercontent.com/ansonhe97/rawimages/master/img/Xnip2019-12-11_17-26-15.jpg"/></div>

As we can see, Rescreen has two Grove ports, one is defualt I2C port and the other is configurable Digital D0, D1 or Analog A0 and A1 ports, as well as UART ports. In this case, analog port is needed so defined as analog input.

Also, initialising the SD Card as follow:

```cpp
#include <SPI.h>
#include <Seeed_FS.h>
#include "SD/Seeed_SD.h"
#include"seeed_line_chart.h" //include the library

File myFile;
TFT_eSPI tft;

#define max_size 30 //maximum size of data
doubles data; //Initilising a doubles type to store data
uint16_t buffer[TFT_WIDTH * TFT_HEIGHT];

int brightness;

void setup() {
    Serial.begin(115200);
    if (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI)) {
        Serial.println("initialization failed!");
        while(1);
  }
    pinMode(A0, INPUT);
    tft.begin();
    tft.setRotation(3);
}
```

- **Reading sensor values and loading data**

```cpp
void loop() {
    brightness = analogRead(A0);
    int brightness = analogRead(LIGHT); //Reading light sensor values

    if (data.size() == max_size) {
        data.pop();//this is used to remove the first read variable
    }
    data.push(brightness); //Storing light sensor values
    saveData(); //Saving data to SD card
    ...
}
```

- **Title configurations**

Please refer to [Line Charts](https://github.com/ansonhe97/GroveUIDocs/blob/master/RescreenDocs/linecharts.md) for more information.

```cpp
//Settings for the line graph title
auto header =  text(0, 0)
            .value("Light Sensor Readings")
            .align(center)
            .valign(vcenter)
            .width(tft.width())
            .thickness(2);

tft.drawToBuffer(buffer); //write to buffer first
tft.fillScreen(TFT_WHITE); //white background

header.height(header.font_height() * 2);
header.draw(); //Header height is the twice the height of the font
```

- **Line Chart configurations**

Please refer to [Line Charts](https://github.com/ansonhe97/GroveUIDocs/blob/master/RescreenDocs/linecharts.md) for more information.

```cpp
//Settings for the line graph
auto content = line_chart(20, header.height()); //(x,y) where the line graph begins
        content
            .height(tft.height() - header.height() * 1.5) //actual height of the line chart
            .width(tft.width() - content.x() * 2) //actual width of the line chart
            .based_on(0.0) //Starting point of y-axis, must be a float
            .show_circle(false) //drawing a cirle at each point, default is on.
            .value(data) //passing through the data to line graph
            .color(TFT_RED) //Setting the color for the line
            .draw();

            tft.drawToTFT();
            tft.pushImage(0,0, tft.width(), tft.height(), buffer);
```

- **Writing Data to SD Card**

Please refer to [Reading/Writing from the SD Card](https://github.com/ansonhe97/GroveUIDocs/blob/master/RescreenDocs/FS/ReadWrite.md) for more information.

```cpp
void saveData(){
     myFile = SD.open("Readings.txt",FILE_APPEND);
     brightness = analogRead(A0);
     Serial.println(brightness);
     myFile.println(brightness);
     myFile.close();
}
```

## Complete code

```cpp
#include <SPI.h>
#include <Seeed_FS.h>
#include "SD/Seeed_SD.h"
#include"seeed_line_chart.h" //include the library

File myFile;
TFT_eSPI tft;

#define max_size 30 //maximum size of data
doubles data; //Initilising a doubles type to store data
uint16_t buffer[TFT_WIDTH * TFT_HEIGHT];
int brightness;

void setup() {
    Serial.begin(115200);
    if (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI)) {
        Serial.println("initialization failed!");
        while(1);
  }
    pinMode(A0, INPUT);
    tft.begin();
    tft.setRotation(3);
}

void loop() {
    brightness = analogRead(A0);

    if (data.size() == max_size) {
        data.pop();//this is used to remove the first read variable
    }
    data.push(brightness); //read variables and store in data
    saveData();

    //Settings for the line graph title
    auto header =  text(0, 0)
                .value("Light Sensor Readings")
                .align(center)
                .valign(vcenter)
                .width(tft.width())
                .thickness(2);

    tft.drawToBuffer(buffer); //write to buffer first
    tft.fillScreen(TFT_WHITE); //white background

    header.height(header.font_height() * 2);
    header.draw(); //Header height is the twice the height of the font

  //Settings for the line graph
    auto content = line_chart(20, header.height()); //(x,y) where the line graph begins
         content
                .height(tft.height() - header.height() * 1.5) //actual height of the line chart
                .width(tft.width() - content.x() * 2) //actual width of the line chart
                .based_on(0.0) //Starting point of y-axis, must be a float
                .show_circle(false) //drawing a cirle at each point, default is on.
                .value(data) //passing through the data to line graph
                .color(TFT_RED) //Setting the color for the line
                .draw();

    tft.drawToTFT();
    tft.pushImage(0,0, tft.width(), tft.height(), buffer);
    delay(100);
}

void saveData(){
     myFile = SD.open("Readings.txt",FILE_APPEND);
     brightness = analogRead(A0);
     Serial.println(brightness);
     myFile.println(brightness);
     myFile.close();
}
```
