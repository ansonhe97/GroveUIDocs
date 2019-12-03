# Rescreen Displaying Accelerator Readings

<div align=center><img src="https://raw.githubusercontent.com/ansonhe97/rawimages/master/img/C0279.2019-11-28%2018_25_43.gif"/></div>

## Overview

This example demonstrates how to draw line graph on Rescreen. In this example, the 3-axis accelerator readings(3 sets of data) are plotted into one line graph to show the real-time positioning of the Rescreen!

### Features

- 3-axis accelerator readings displying in one Line graph

- Real time positioning of the Rescreen

## Arduino libraries needed

- Install the Line Chart library `rescreen_graphics`, please visit [Line Charts](https://github.com/ansonhe97/GroveUIDocs/blob/master/RescreenDocs/linecharts.md) for more information.

- Install the on-board accelerator library `Seeed_Arduino_LIS3DHTR`, Please visit [Seeed_Arduino_LIS3DHTR](https://github.com/Seeed-Studio/Seeed_Arduino_LIS3DHTR) for more information.

## Arduino Instructions

1. It is highly recommended to read through [Line Charts](https://github.com/ansonhe97/GroveUIDocs/blob/master/RescreenDocs/linecharts.md) first and before trying out this example code.

2. Download the `AcceratorReadings.ino` file and upload to your Rescreen through `Adruino IDE`. Make sure you installed all the libraries.

3. Move Rescreen in different axis and see what it displays, and you could also open `Serial Plotter` to check the effect!

## Code

- **To intialise LCD and Acclerator**

```cpp
#include"LIS3DHTR.h" //include the accelerator library
#include"seeed_line_chart.h" //include the line chart library
TFT_eSPI tft;
LIS3DHTR<TwoWire>  lis;

#define max_size 50 //maximum size of data
doubles accelerator_readings[3]; // initialising a doubles array to store data


uint16_t buffer[TFT_WIDTH * TFT_HEIGHT]; //Buffer

void setup() {
    tft.begin();
    tft.setRotation(3);

    lis.begin(Wire1);
    lis.setOutputDataRate(LIS3DHTR_DATARATE_25HZ);
    lis.setFullScaleRange(LIS3DHTR_RANGE_2G);

    Serial.begin(115200);
}
```

- **Reading Accelerator data and loading data**

Please refer to [Line Charts](https://github.com/ansonhe97/GroveUIDocs/blob/master/RescreenDocs/linecharts.md) for more information.

```cpp
void loop() {
    float x_raw = lis.getAccelerationX();
    float y_raw = lis.getAccelerationY();
    float z_raw = lis.getAccelerationZ();
    ...

    if (accelerator_readings[0].size() == max_size) {
      for (uint8_t i = 0; i<3; i++){
        accelerator_readings[i].pop(); //this is used to remove the first read variable
      }
    }

    accelerator_readings[0].push(x_raw); //store x-axis readings
    accelerator_readings[1].push(y_raw); //store y-axis readings
    accelerator_readings[2].push(z_raw); //store z-axis readings
    ...
}
```

- **Title configurations**

Please refer to [Line Charts](https://github.com/ansonhe97/GroveUIDocs/blob/master/RescreenDocs/linecharts.md) for more information.

```cpp
auto header =  text(0, 0)
            .value("Accelerator Readings")
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

To draw multiple lines in one graph, you can pass doubles array into the line graph like `cotent.value({doubles[0],doubles[1],doubles[2]...})` as shown below. Can also set the color for each line using `.color()` where the order of color will match the order of data passing.

```cpp
auto content = line_chart(20, header.height()); //(x,y) where the line graph begins
     content
            .height(tft.height() - header.height() * 1.5) //actual height of the line chart
            .width(tft.width() - content.x() * 2) //actual width of the line chart
            .based_on(-2.0) //Starting point of y-axis, must be a float
            .show_circle(false) //drawing a cirle at each point, default is on.
            .value({accelerator_readings[0],accelerator_readings[1], accelerator_readings[2]}) //passing through the data to line graph
            .color(TFT_BLUE, TFT_RED, TFT_GREEN) //color for each line
            .draw();
```

## Complete code 

```cpp
#include"LIS3DHTR.h" //include the accelerator library
#include"seeed_line_chart.h" //include the line chart library
TFT_eSPI tft;
LIS3DHTR<TwoWire>  lis;

#define max_size 50 //maximum size of data
doubles accelerator_readings[3];


uint16_t buffer[TFT_WIDTH * TFT_HEIGHT];

void setup() {
    tft.begin();
    tft.setRotation(3);

    lis.begin(Wire1);
    lis.setOutputDataRate(LIS3DHTR_DATARATE_25HZ);
    lis.setFullScaleRange(LIS3DHTR_RANGE_2G);

    Serial.begin(115200);
}

void loop() {
    float x_raw = lis.getAccelerationX();
    float y_raw = lis.getAccelerationY();
    float z_raw = lis.getAccelerationZ();

    //This is used to print out on Serial Plotter, check Serial Plotter!
    Serial.print(x_raw);
    Serial.print(",");
    Serial.print(y_raw);
    Serial.print(",");
    Serial.println(z_raw);

    if (accelerator_readings[0].size() == max_size) {
      for (uint8_t i = 0; i<3; i++){
        accelerator_readings[i].pop(); //this is used to remove the first read variable
      }
    }
    accelerator_readings[0].push(x_raw); //read variables and store in data
    accelerator_readings[1].push(y_raw);
    accelerator_readings[2].push(z_raw);

    //Settings for the line graph title
    auto header =  text(0, 0)
                .value("Accelerator Readings")
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
                .based_on(-2.0) //Starting point of y-axis, must be a float
                .show_circle(false) //drawing a cirle at each point, default is on.
                .value({accelerator_readings[0],accelerator_readings[1], accelerator_readings[2]}) //passing through the data to line graph
                .color(TFT_BLUE, TFT_RED, TFT_GREEN)
                .draw();

    tft.drawToTFT();
    tft.pushImage(0,0, tft.width(), tft.height(), buffer);
    delay(50);
}
```