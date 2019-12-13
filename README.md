# Getting Started with ReScreen

## Introduction

Grove UI is the next generation, fully integrated high-end development platform, with a 2.4inch LCD Screen, Wi-Fi and Bluetooth connectivity enabled by ESP32, and is powered by the Atmel ATSAMD51 Chip.

## Software

To interact with ReScreen, Arduino IDE is needed.

- Download Arduino IDE from [here](https://www.arduino.cc/en/main/software), choose the verison according to your operating system.

## Arduino Configurations

Once Arduino IDE is installed, some configurations need to be done:

1. Navigate to Arduino Preferences, and copy the following Seeed Studio Boards manger url to `Additional Boards Manger URLs:` as follow

`https://raw.githubusercontent.com/Seeed-Studio/Seeed_Platform/master/package_seeeduino_boards_index.json`

<div align=center><img width = 600 src="https://raw.githubusercontent.com/ansonhe97/rawimages/master/img/Xnip2019-12-13_09-41-25.jpg"/></div>

2. Navigate to `Tools` -> `Board:` -> `Boards Manger...` on top of Arduino IDE. Search **Seeed SAMD Boards** in `Boards Manager` and install.

<div align=center><img width = 500 src="https://raw.githubusercontent.com/ansonhe97/rawimages/master/img/Arduino.jpg"/></div>

1. Now, you can upload your program to ReScreen by selecting the corrent port and **Seeeduino ReScreen(SAMD51)** as Board!
