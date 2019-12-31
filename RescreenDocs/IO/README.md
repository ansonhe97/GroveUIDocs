# Overview

This repo introduce how to use the Grove IOs on the ReScreen. This allows you to enjoy the plug and play functionality of the Grove Ecosystem!

## Hardware Schematics

### RsScreen RPI Pinout

<div align=center><img width = 600 src="https://raw.githubusercontent.com/ansonhe97/rawimages/master/img/Xnip2019-12-13_14-16-23.jpg"/></div>

ReScreen has 40 GPIOs breaking out from the SAMD51, which has the same breakout as the Raspberry Pi!

#### *To reference defined pinout names, please check `variant.h`*

### ReScreen Grove Port Pinout

<div align=center><img width=400 src="https://raw.githubusercontent.com/ansonhe97/rawimages/master/img/Xnip2019-12-11_17-26-15.jpg"/></div>

As you can see, There are two Grove Ports available on ReScreen. One is the default **I2C Port** and other one is default **UART Port**. Both ports can be used as Digital Ports, I2C Port can also be used as PWM Outputs.
