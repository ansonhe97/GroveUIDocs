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
#define BUTTON D0
#define LED PIN_WIRE_SCL

void setup() {
    Serial.begin(115200);
    pinMode(BUTTON, INPUT);
    pinMode(LED, OUTPUT);
}
void loop() {
    int buttonState = digitalRead(BUTTON);
    Serial.print("Button State: ");
    Serial.println(buttonState);

    if (buttonState == HIGH) {
        digitalWrite(LED, HIGH);
    }
    else {
        digitalWrite(LED, LOW);
    }
    delay(50);
}
```