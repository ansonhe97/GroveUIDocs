# Using the Grove Analog Port on Rescreen

<div align=center><img src="https://raw.githubusercontent.com/ansonhe97/rawimages/master/img/2019-12-12%2011-36-22.2019-12-12%2011_37_02.gif"/></div>

This repo demonstrates how to use the Grove Analog Port on Rescreen, you can simply use this plug and play functionality with the Grove Ecosystem!

## Port Configurations

To use the Grove Port as Analog port, simply define it as follow:

**Note:** A0 and A1 are the same Grove Port.

```cpp
void setup() {
    pinMode(A0, INPUT); //Configure as A0 analog port
}
```

Now, connect your Grove sensor to the physical Grove Port!

## Example Code 

In this example, a Grove Loudness sensor is used to demonstrate:

```cpp
void setup() {
    Serial.begin(115200);
    pinMode(A0, INPUT);
}
void loop() {
    int loudness = analogRead(A0);
    Serial.print("Loudness: ");
    Serial.println(loudness);
    delay(50);
}
}
```