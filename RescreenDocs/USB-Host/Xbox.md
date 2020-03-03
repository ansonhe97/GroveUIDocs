# Using Xbox ONE Controller on ReScreen

This repo introduces how to use a Xbox ONE Controller on ReScreen. With this exmaple, you can implement to use a Xbox Controller to play games using the ReScreen!

<div align=center><img width = 500 src="https://files.seeedstudio.com/wiki/Wio-Terminal/img/20200109132336.gif"/></div>

## Requirements

To work with this exmaple, you will need a **USB OTG Adaptor** and a **USB to Serial Module**, where the OTG adaptor is used to connect with keyboard and the USB to Serial module to read the outputs from ReScreen.

**Note:** Xbox ONE Controller is used in this exmaple. If using Xbox 360 controller or clone ones, please check `XBOXOLD.ino` in the exmaple.

## Procedures

1. Upload the code to ReScreen using `Arduino IDE`.

2. Unplug the USB type-C cable from ReScreen that used to upload the code.

3. Connect your **Xbox ONE Controller** to the **OTG adaptor** then to the USB-C port of ReScreen.
   - **`Xbox ONE Controller`** -> **`OTG Adaptor`** -> **`ReScreen(Type-C Port)`**

4. Connect the **USB to Serial Module** to the ReScreen as follow:
   - **`TXD(USB to Serial Module)`** -> **`RXD(Pin 10 on ReScreen)`**
   - **`RXD(USB to Serial Module)`** -> **`TXD(Pin 8 on ReScreen)`**
   - **`3.3V(USB to Serial Module)`** -> **`3.3V(Pin 1 on ReScreen)`**
   - **`GND(USB to Serial Module)`** -> **`GND(Pin 6 on ReScreen)`**

5. Connect the USB to Serial Module to your computer. Depending on what USB to Serial Module used, **download the USB driver** for the module so that your computer can recognise it.

6. For Windows User, you can open Device Manager to check if it's recogniesd. A new `COM` should appear.
   - For Mac user, use `ls /dev/cu.*` in terminal to check the module availbility.

7. To view data from Serial:
   - **Windows:** Download and install [PuTTY](https://www.putty.org/). Select `Serial` and change the `COM` in Serial line to the COM that appeared in the Device Manager, also change the Speed. to `115200` and press Open. A Terminal should appear. Now, if you start pressing buttons on Xbox ONE controller, you should see the serial output!

   - **Mac:** Open terminal and install `screen` using `brew install screen`. Once installed, use the command **`screen /dev/cu.usbserial 115200`** where `/dev/cu.usbserial` should match from above. You should be see serial output from ReScreen!

**Important Note:** Because the USB port of ReScreen is being used for USB, to upload another program to ReScreen require entering Bootloader mode by pressing the power button twice(the LED will dim), then you should be able see the port again.

## Complete Code

```cpp
#include <XBOXONE.h>
#define SerialDebug Serial1

USBHost UsbH;
XBOXONE Xbox(&UsbH);

void setup() {
  SerialDebug.begin(115200);
  if (UsbH.Init()) {
    SerialDebug.print(F("\r\nUSB host did not start"));
    while (1); //halt
  }
  SerialDebug.print(F("\r\nXBOX USB Library Started"));
}
void loop() {
  UsbH.Task();
  if (Xbox.XboxOneConnected) {
    if (Xbox.getAnalogHat(LeftHatX) > 7500 || Xbox.getAnalogHat(LeftHatX) < -7500 || Xbox.getAnalogHat(LeftHatY) > 7500 || Xbox.getAnalogHat(LeftHatY) < -7500 || Xbox.getAnalogHat(RightHatX) > 7500 || Xbox.getAnalogHat(RightHatX) < -7500 || Xbox.getAnalogHat(RightHatY) > 7500 || Xbox.getAnalogHat(RightHatY) < -7500) {
      if (Xbox.getAnalogHat(LeftHatX) > 7500 || Xbox.getAnalogHat(LeftHatX) < -7500) {
        SerialDebug.print(F("LeftHatX: "));
        SerialDebug.print(Xbox.getAnalogHat(LeftHatX));
        SerialDebug.print("\t");
      }
      if (Xbox.getAnalogHat(LeftHatY) > 7500 || Xbox.getAnalogHat(LeftHatY) < -7500) {
        SerialDebug.print(F("LeftHatY: "));
        SerialDebug.print(Xbox.getAnalogHat(LeftHatY));
        SerialDebug.print("\t");
      }
      if (Xbox.getAnalogHat(RightHatX) > 7500 || Xbox.getAnalogHat(RightHatX) < -7500) {
        SerialDebug.print(F("RightHatX: "));
        SerialDebug.print(Xbox.getAnalogHat(RightHatX));
        SerialDebug.print("\t");
      }
      if (Xbox.getAnalogHat(RightHatY) > 7500 || Xbox.getAnalogHat(RightHatY) < -7500) {
        SerialDebug.print(F("RightHatY: "));
        SerialDebug.print(Xbox.getAnalogHat(RightHatY));
      }
      SerialDebug.println();
    }

    if (Xbox.getButtonPress(L2) > 0 || Xbox.getButtonPress(R2) > 0) {
      if (Xbox.getButtonPress(L2) > 0) {
        SerialDebug.print(F("L2: "));
        SerialDebug.print(Xbox.getButtonPress(L2));
        SerialDebug.print("\t");
      }
      if (Xbox.getButtonPress(R2) > 0) {
        SerialDebug.print(F("R2: "));
        SerialDebug.print(Xbox.getButtonPress(R2));
        SerialDebug.print("\t");
      }
      SerialDebug.println();
    }

    // Set rumble effect
    static uint16_t oldL2Value, oldR2Value;
    if (Xbox.getButtonPress(L2) != oldL2Value || Xbox.getButtonPress(R2) != oldR2Value) {
      oldL2Value = Xbox.getButtonPress(L2);
      oldR2Value = Xbox.getButtonPress(R2);
      uint8_t leftRumble = map(oldL2Value, 0, 1023, 0, 255); // Map the trigger values into a byte
      uint8_t rightRumble = map(oldR2Value, 0, 1023, 0, 255);
      if (leftRumble > 0 || rightRumble > 0)
        Xbox.setRumbleOn(leftRumble, rightRumble, leftRumble, rightRumble);
      else
        Xbox.setRumbleOff();
    }

    if (Xbox.getButtonClick(UP))
      SerialDebug.println(F("Up"));
    if (Xbox.getButtonClick(DOWN))
      SerialDebug.println(F("Down"));
    if (Xbox.getButtonClick(LEFT))
      SerialDebug.println(F("Left"));
    if (Xbox.getButtonClick(RIGHT))
      SerialDebug.println(F("Right"));

    if (Xbox.getButtonClick(START))
      SerialDebug.println(F("Start"));
    if (Xbox.getButtonClick(BACK))
      SerialDebug.println(F("Back"));
    if (Xbox.getButtonClick(XBOX))
      SerialDebug.println(F("Xbox"));
    if (Xbox.getButtonClick(SYNC))
      SerialDebug.println(F("Sync"));

    if (Xbox.getButtonClick(L1))
      SerialDebug.println(F("L1"));
    if (Xbox.getButtonClick(R1))
      SerialDebug.println(F("R1"));
    if (Xbox.getButtonClick(L2))
      SerialDebug.println(F("L2"));
    if (Xbox.getButtonClick(R2))
      SerialDebug.println(F("R2"));
    if (Xbox.getButtonClick(L3))
      SerialDebug.println(F("L3"));
    if (Xbox.getButtonClick(R3))
      SerialDebug.println(F("R3"));


    if (Xbox.getButtonClick(A))
      SerialDebug.println(F("A"));
    if (Xbox.getButtonClick(B))
      SerialDebug.println(F("B"));
    if (Xbox.getButtonClick(X))
      SerialDebug.println(F("X"));
    if (Xbox.getButtonClick(Y))
      SerialDebug.println(F("Y"));
  }
  delay(1);
}
```