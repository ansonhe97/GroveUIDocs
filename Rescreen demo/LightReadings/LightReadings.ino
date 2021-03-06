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
