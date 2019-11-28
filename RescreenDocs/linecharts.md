# Line Charts

This repo describes how to draw line graphs on Rescreen. You can use this to diaplay raw sensor values to visualise readings on screen just like the serial plotter! The library is very flexible and can alter to your own need.

<div align=center><img src="https://raw.githubusercontent.com/ansonhe97/rawimages/master/img/C0277.2019-11-27%2018_19_05.gif"/></div>

## Libraries Installation

### Installing the Rescreen_graphics Libaray For 2D Graphic For Rescreen

- visit [Rescreen_graphics Libaray For 2D Graphics](https://github.com/PowerfulCat/Works/tree/master/rescreen_graphics) and download the entire repo to your local drive.

- Now, the Rescreen_graphics library can be installed to the Arduino IDE. Open the Arduino IDE, and click `sketch` -> `Include Library` -> `Add .ZIP Library`, and choose the `rescreen_graphics` file that you've have just downloaded.

![InstallLibrary](https://raw.githubusercontent.com/ansonhe97/rawimages/master/img/Xnip2019-11-21_15-50-13.jpg)

## Getting Started

### To initialise for drawing Line graph

At first, defining the maximun number of variables to be stored, and a vector to store datal, as well as creating a buffer array.

```cpp
#define max_size 50 //maximum size of variables
std::vector<double> data; //vector to store the data
uint16_t buffer[TFT_WIDTH * TFT_HEIGHT]; //buffer area with same size of the screen
```

### To inilitialise the LCD Screen

```cpp
void setup() {
    tft.begin();
    tft.setRotation(3);
}
```

### Loading variables to data

Use `data.push_back(vairable)` to store variables (i.e. sensor readings) in data, and if it reached the pre-defined maximum number it removes the first variable (keep on going).

```cpp
    if (data.size() == max_size) { 
        data.erase(data.begin()); //this is used to remove the first read variable
    }
        data.push_back(0.01 * random(1, 10)); //read variables and store in data
```

### To initilise settings for the Line Graph Title

Some settings to configure the desired display of the title for line graph. Initilise a `text(x, y)` struct, where `(x, y)` is the starting coordinates of the title. And configure settings as below. In this example, `header` is the name of this struct and can change settings and configure like `header.value("test")` and etc.

```cpp
    //Settings for the line graph title
auto header =   text(0, 0)           //starting coordinates of title
                .value("test")      //actual title of the line graph
                .align(center)      //horizontal alignment of title
                .valign(vcenter)    //vertical alignment of title
                .width(tft.width()) //width of the title
                .thickness(3);      //thickness of the font

    tft.drawToBuffer(buffer);       //write to buffer first
    tft.fillScreen(TFT_WHITE);      //white background, can change to different color

    header.height(header.font_height() * 2); //the height of title is the twice the height of the font
    header.draw(); 
```

To help understanding this exmaple code, please refer the title configurations to the image below:

<div align=center><img src="https://raw.githubusercontent.com/ansonhe97/rawimages/master/img/title.png"/></div>


### To initilise settings for the Line Graph and Draw on the LCD Screen

Some settings to configure the desired display of the Line graph. Initialise a `line_chart(x, y)` struct, where `(x, y)` is the starting coordinate of the line graph. And configure settings as below. In this example, `content` is the name of this struct and can change settings and configure like `content.based_on(0.0)` and etc. Alter these settings for prefer display!

```cpp
  //Settings for the line graph
    auto content = line_chart(20, header.height()); //(x,y) where the line graph begins
                 content
                .height(tft.height() - header.height() * 1.5) //actual height of the line chart
                .width(tft.width() - content.x() * 2) //actual width of the line chart
                .based_on(0.0) //Starting point of y-axis, must be a float
                .show_circle(false) //drawing a cirle at each point, default is on.
                .value(data) //passing through the data to line graph
                .draw();

    tft.drawToTFT(); //draw from buffer to the tft screen
    tft.pushImage(0,0, tft.width(), tft.height(), buffer); 
```

To help understanding this exmaple code, please refer the line graph configurations to the image below:

<div align=center><img src="https://raw.githubusercontent.com/ansonhe97/rawimages/master/img/linegraph2.png"/></div>

## Complete code

```cpp
#include"seeed_line_chart.h" //include the library
TFT_eSPI tft;

#define max_size 50 //maximum size of data
std::vector<double> data; //vector to store such data 

uint16_t buffer[TFT_WIDTH * TFT_HEIGHT];

void setup() {
    tft.begin();
    tft.setRotation(3);
}

void loop() {
    if (data.size() == max_size) {
        data.erase(data.begin()); //this is used to remove the first read variable
    }
    data.push_back(0.01 * random(1, 10)); //read variables and store in data

    //Settings for the line graph title
    auto header =  text(0, 0)
                .value("test")
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
                .show_circle(false) //drawing a cirle at each point, default is on.
                .value(data) //passing through the data to line graph
                .draw();

    tft.drawToTFT();
    tft.pushImage(0,0, tft.width(), tft.height(), buffer);
}
```