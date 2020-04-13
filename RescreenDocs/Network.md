# Overview

This wiki introduce how to update the latest firmware for the Wireless Core Realtek RTL8720 on Wio Terminal, as well as installing all the dependent libraries for Wio Terminal to enable wireless connectivity.

## Update the Wireless Core Firmware

First, we need to update the firmware for the Realtek RTL8720 Wireless core on Wio Terminal. **This is essential and must update to the latest firmware before proceeding to examples.**

### Step 1 - Arduino Configuration

To be able to update the firmware on the RTL8720, we need to enable the Serial connection from SAMD51 to RTL8720. This is done by a simple Arduino Program.

- Download the [**`rtl8720_update.ino`**](https://files.seeedstudio.com/wiki/Wio-Terminal/res/rtl8720_update.zip) Arduino program, or Copy the following code to the Arduino IDE.

```cpp
void setup() {
  // initialize both serial ports:
  pinMode(PIN_SERIAL2_RX, OUTPUT);
  pinMode(RTL8720D_CHIP_PU, OUTPUT);
  digitalWrite(PIN_SERIAL2_RX, LOW);
  digitalWrite(RTL8720D_CHIP_PU, LOW);
  delay(500);
  digitalWrite(RTL8720D_CHIP_PU, HIGH);
  delay(500);
  pinMode(PIN_SERIAL2_RX, INPUT);
  Serial.beginWithoutDTR(115200);
//  Serial.baud
  RTL8720D.begin(115200);

  delay(500);
}

void loop() {

  // read from port 1, send to port 0:
  if (Serial.available()) {
    int inbyte = Serial.read();
    RTL8720D.write(inbyte);
    //Serial1.write(inbyte);
  }
//   read from port 1, send to port 0:
  if (RTL8720D.available()) {
    int inbyte = RTL8720D.read();
    Serial.write(inbyte);
    //Serial1.write(inbyte);
  }
}
```

- **Upload** the Arduino Program to Wio Terminal.

<div align=center><img width = 500 src="https://files.seeedstudio.com/wiki/Wio-Terminal/img/rtl-ard.png"/></div>

### Step 2 - Download the Image Tool

Next up, download the [**Image Tool**](https://files.seeedstudio.com/wiki/Wio-Terminal/res/ameba-image-Tool-v2.4.1.zip) here. This is the tool for uploading the latest firmware to the RTL8720 on Wio Terminal.

**Note:** For now, the Image Tool is only available in **Windows**. Image Tool for Linux OS and Mac OS will be available very soon.

### Step 3 - Download the Latest Firmware

Download the latest [**RTL8720 Firmware**]() Here.

### Step 4 - Updating the Firmware

- Open the **`ImageTool.exe`** tool. Click on the **Chip Select** and Select the **AmebaD(8721D)** on the top left corner.

<div align=center><img width = 300 src="https://files.seeedstudio.com/wiki/Wio-Terminal/img/Select-chip.png"/></div>

- **Select the correct Serial Port for Wio Terminal.** In my case, it's COM11. Set the Baudrate to **115200**. Under **Flash Download** session, click on **Browse**:

<div align=center><img width = 450 src="https://files.seeedstudio.com/wiki/Wio-Terminal/img/Select-port.png"/></div>

- Choose the **RTL8720 Firmware** file that you downloaded from above, **tick the box**, and click on **Download** to load the firmware:

**Note:** Make sure the Baudrate is set to 115200.

<div align=center><img width = 450 src="https://files.seeedstudio.com/wiki/Wio-Terminal/img/Select-firmware.png"/></div>

- The RTL8720 firmware will start writing to the chip on Wio Terminal, please wait patiently until it's done:

<div align=center><img width = 450 src="https://files.seeedstudio.com/wiki/Wio-Terminal/img/update.png"/></div>

- Once it's uploaded successfully, you should be to see a window as shown:

<div align=center><img width = 450 src="https://files.seeedstudio.com/wiki/Wio-Terminal/img/rtl-done.png"/></div>

Now, the latest RTL8720 firmware is loaded onto the board.

## Libraries Installation

There are few Arduino Libraries that are needed for the Wireless connectivity. Follow through to install all the libraries needed:

### 1. Install the Seeed_Arduino_atWiFi

1. Visit the [Seeed_Arduino_atWiFi](https://github.com/Seeed-Studio/Seeed_Arduino_atWiFi) repositories and download the entire repo to your local drive.

2. Now, the Seeed_Arduino_atWiFi library can be installed to the Arduino IDE. Open the Arduino IDE, and click `sketch` -> `Include Library` -> `Add .ZIP Library`, and choose the `Seeed_Arduino_atWiFi` file that you've have just downloaded.

![InstallLibrary](https://files.seeedstudio.com/wiki/Wio-Terminal/img/Xnip2019-11-21_15-50-13.jpg)

### 2. Install the Seeed-Arduino-FreeRTOS

1. Visit the [Seeed-Arduino-FreeRTOS](https://github.com/Seeed-Studio/Seeed_Arduino_FreeRTOS) repositories and download the entire repo to your local drive.

2. Now, the Seeed-Arduino-FreeRTOS library can be installed to the Arduino IDE. Open the Arduino IDE, and click `sketch` -> `Include Library` -> `Add .ZIP Library`, and choose the `Seeed-Arduino-FreeRTOS` file that you've have just downloaded.

### 3. Install Seeed_Arduino_atUnified

1. Visit the [Seeed_Arduino_atUnified](https://github.com/Seeed-Studio/Seeed_Arduino_atUnified) repositories and download the entire repo to your local drive.

2. Now, the Seeed_Arduino_atUnified library can be installed to the Arduino IDE. Open the Arduino IDE, and click `sketch` -> `Include Library` -> `Add .ZIP Library`, and choose the `Seeed_Arduino_atUnified` file that you've have just downloaded.

### 4. Install Seeed_Arduino_atWiFi

1. Visit the [Seeed-Studio/esp-at-lib](https://github.com/Seeed-Studio/esp-at-lib) repositories and download the entire repo to your local drive.

2. Now, the esp-at-lib library can be installed to the Arduino IDE. Open the Arduino IDE, and click `sketch` -> `Include Library` -> `Add .ZIP Library`, and choose the `esp-at-lib` file that you've have just downloaded.