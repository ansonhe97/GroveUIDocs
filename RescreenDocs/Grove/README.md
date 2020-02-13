# Overview

This repo introduces how to use Wio Terminal with the [**Grove Ecosystem**](https://www.seeedstudio.com/grove.html).

With the help of Grove, you are able prototype much quicker with simpler connections!

## Wio Terminal With Grove - TDS Sensor

This section introduces how to use [Grove - TDS Sensor](http://wiki.seeedstudio.com/Grove-TDS-Sensor/) with Wio Terminal to display real time TDS readings on a line chart!

### Libraries Installation

1. Install the [LCD](https://github.com/ansonhe97/GroveUIDocs/tree/master/RescreenDocs/LCD) library.

2. Install the [Linechart](https://github.com/ansonhe97/GroveUIDocs/blob/master/RescreenDocs/LCD/linecharts.md) library.

### Complete Code

Connect the Grove TDS sensor to the Grove D/A Pin of Wio Terminal, upload the code and check the results!

```cpp
#include"seeed_line_chart.h" //include the library

TFT_eSPI tft;
#define sensorPin A0 //Analog pin

int sensorValue = 0;
float tdsValue = 0;
float Voltage = 0;

#define max_size 20 //maximum size of data
doubles data; //Initilising a doubles type to store data

uint16_t buffer[TFT_WIDTH * TFT_HEIGHT];

void setup() {
    tft.begin();
    tft.setRotation(3);
    Serial.begin(115200);
}

void loop() {
    sensorValue = analogRead(sensorPin);
    Voltage = sensorValue*5/1024.0; //Convert analog reading to Voltage
    tdsValue=(133.42*Voltage*Voltage*Voltage - 255.86*Voltage*Voltage + 857.39*Voltage)*0.5; //Convert voltage value to TDS value

    if (data.size() == max_size) {
        data.pop();//this is used to remove the first read variable
    }
    data.push(tdsValue); //read TDS values and store in data

    //Settings for the line graph title
    auto header =  text(0, 0)
                .value("TDS Reading")
                .align(center)
                .valign(vcenter)
                .width(tft.width())
                .thickness(3);

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
                .show_circle(true) //drawing a cirle at each point, default is on.
                .value(data) //passing through the data to line graph
                .color(TFT_RED) //Setting the color for the line
                .draw();

    tft.drawToTFT();
    tft.pushImage(0,0, tft.width(), tft.height(), buffer);
    delay(50);
}
```