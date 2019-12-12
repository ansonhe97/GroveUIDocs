# Using the Grove Digital Port on Rescreen

<div align=center><img src="https://raw.githubusercontent.com/ansonhe97/rawimages/master/img/2019-12-12%2014-55-44.2019-12-12%2014_56_10.gif"/></div>

This repo demonstates how to use the Grove Digital Port on ReScreen, you can simply use this functionality with the Groe Ecosystem!

## Port Configurations

To use the Grove Port as Digital port, simply define it as follow:

**Note:** D0 and D1 are the same Grove Port.

```cpp
void setup() {
    pinMode(D0, INPUT); //Configure as D0 Digital port
}
```

### Using PWM output

The Grove ports on ReScreen can also be used as PWM output.


### Using I2C as Digital Port

The Grove I2C port can also be used as Digital Port on Rescreen:

```cpp
void setup() {
    pinMode(PIN_WIRE_SCL, INPUT); //Defined SCL of I2C port as Digital Input
```

Now, connect your Grove sensor to the physical Grove Port!

**Note:** For more defined variant pin name, please check Schematic and variant.h

## Example Code

In this example, a Grove Button and Grove LED are used to demonstrate:

```cpp
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

void setup() 
{
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    
    lcd.setRGB(colorR, colorG, colorB);
    
    // Print a message to the LCD.
    lcd.print("hello, world!");

    delay(1000);
}

void loop() 
{
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    lcd.print(millis()/1000);

    delay(100);
}
```

## PWM Output Example Code (Servo)

In this example, a Grove Servo is used to demonstrate PWM output:

```cpp
#include <Servo.h>
Servo myservo;

int pos = 0;

void setup() {
  myservo.attach(D0); //Connect servo to D0
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) {
    // in steps of 1 degree
    myservo.write(pos);
    delay(15);
  }
  for (pos = 180; pos >= 0; pos -= 1) {
    myservo.write(pos);
    delay(15);
  }
}
```

**Note:** To use the Servo library with ReScreen, please include [Adafruit's version](https://github.com/PaintYourDragon/Servo) for SAMD51 capability.