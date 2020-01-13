# Using USB Mouse on ReScreen

This repo introduces how to use a USB Mouse on ReScreen. You can implement this example to input data from a Keyboard to ReScreen!

<div align=center><img width = 500 src="https://raw.githubusercontent.com/ansonhe97/rawimages/master/img/20200108160611.gif"/></div>

## Requirements

To work with this exmaple, you will need a **USB OTG Adaptor** and a **USB to Serial Module**, where the OTG adaptor is used to connect with keyboard and the USB to Serial module to read the outputs from ReScreen.

## Procedures

1. Upload the code to ReScreen using `Arduino IDE`.

2. Unplug the USB type-C cable from ReScreen that used to upload the code.

3. Connect your **Mouse** to the **OTG adaptor** then to the USB-C port of ReScreen.
   - **`Mouse`** -> **`OTG Adaptor`** -> **`ReScreen(Type-C Port)`**

4. Connect the **USB to Serial Module** to the ReScreen as follow:
   - **`TXD(USB to Serial Module)`** -> **`RXD(Pin 10 on ReScreen)`**
   - **`RXD(USB to Serial Module)`** -> **`TXD(Pin 8 on ReScreen)`**
   - **`3.3V(USB to Serial Module)`** -> **`3.3V(Pin 1 on ReScreen)`**
   - **`GND(USB to Serial Module)`** -> **`GND(Pin 6 on ReScreen)`**

5. Connect the USB to Serial Module to your computer. Depending on what USB to Serial Module used, **download the USB driver** for the module so that your computer can recognise it.

6. For Windows User, you can open Device Manager to check if it's recogniesd. A new `COM` should appear.
   - For Mac user, use `ls /dev/cu.*` in terminal to check the module availbility.

7. To view data from Serial:
   - **Windows:** Download and install [PuTTY](https://www.putty.org/). Select `Serial` and change the `COM` in Serial line to the COM that appeared in the Device Manager, also change the Speed. to `115200` and press Open. A Terminal should appear. Now, if you start pressing and moving the mouse, you should see the serial output!

   - **Mac:** Open terminal and install `screen` using `brew install screen`. Once installed, use the command **`screen /dev/cu.usbserial 115200`** where `/dev/cu.usbserial` should match from above. You should be see serial output from ReScreen!

**Important Note:** Because the USB port of ReScreen is being used for USB, to upload another program to ReScreen require entering Bootloader mode by pressing the power button twice(the LED will dim), then you should be able see the port again.

## Complete Code

```cpp
#include <MouseController.h>
#define SerialDebug Serial1

uint32_t lastUSBstate = 0;

// Initialize USB Controller
USBHost usb;

// Attach mouse controller to USB
MouseController mouse(usb);

// variables for mouse button states
bool leftButton = false;
bool middleButton = false;
bool rightButton = false;

// This function intercepts mouse movements
void mouseMoved() {
  SerialDebug.print("Move: ");
  SerialDebug.print(mouse.getXChange());
  SerialDebug.print(", ");
  SerialDebug.println(mouse.getYChange());
}

// This function intercepts mouse movements while a button is pressed
void mouseDragged() {
  SerialDebug.print("DRAG: ");
  SerialDebug.print(mouse.getXChange());
  SerialDebug.print(", ");
  SerialDebug.println(mouse.getYChange());
}

// This function intercepts mouse button press
void mousePressed() {
  SerialDebug.print("Pressed: ");
  if (mouse.getButton(LEFT_BUTTON)) {
    SerialDebug.print("L");
    leftButton = true;
  }
  if (mouse.getButton(MIDDLE_BUTTON)) {
    SerialDebug.print("M");
    middleButton = true;
  }
  if (mouse.getButton(RIGHT_BUTTON)) {
    SerialDebug.print("R");
    rightButton = true;
  }
  SerialDebug.println();
}

// This function intercepts mouse button release
void mouseReleased() {
  SerialDebug.print("Released: ");
  if (!mouse.getButton(LEFT_BUTTON) && leftButton == true) {
    SerialDebug.print("L");
    leftButton = false;
  }
  if (!mouse.getButton(MIDDLE_BUTTON) && middleButton == true) {
    SerialDebug.print("M");
    middleButton = false;
  }
  if (!mouse.getButton(RIGHT_BUTTON) && rightButton == true) {
    SerialDebug.print("R");
    rightButton = false;
  }
  SerialDebug.println();
}

void setup()
{
  SerialDebug.begin( 115200 );
  SerialDebug.println("Mouse Controller Program started");

  if (usb.Init())
      SerialDebug.println("USB host did not start.");

  delay( 20 );
}

void loop()
{
  // Process USB tasks
  usb.Task();

  uint32_t currentUSBstate = usb.getUsbTaskState();
  if (lastUSBstate != currentUSBstate) {
    SerialDebug.print("USB state changed: 0x");
    SerialDebug.print(lastUSBstate, HEX);
    SerialDebug.print(" -> 0x");
    SerialDebug.println(currentUSBstate, HEX);
    switch (currentUSBstate) {
      case USB_ATTACHED_SUBSTATE_SETTLE: SerialDebug.println("Device Attached"); break;
      case USB_DETACHED_SUBSTATE_WAIT_FOR_DEVICE: SerialDebug.println("Detached, waiting for Device"); break;
      case USB_ATTACHED_SUBSTATE_RESET_DEVICE: SerialDebug.println("Resetting Device"); break;
      case USB_ATTACHED_SUBSTATE_WAIT_RESET_COMPLETE: SerialDebug.println("Reset complete"); break;
      case USB_STATE_CONFIGURING: SerialDebug.println("USB Configuring"); break;
      case USB_STATE_RUNNING: SerialDebug.println("USB Running"); break;
    }
    lastUSBstate = currentUSBstate;
  }
}
```