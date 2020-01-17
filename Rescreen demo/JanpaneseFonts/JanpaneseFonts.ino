#include<SPI.h>
#include "Seeed_FS.h"
#include "SD/Seeed_SD.h"
#include"TFT_eSPI.h"

TFT_eSPI tft;

void setup() {
    tft.begin();
    Serial.begin(115200);
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK); //Black background

    while(!SD.begin(SDCARD_SS_PIN, SDCARD_SPI)){
        Serial.println("SD card error!\n");
        while(1);
  }
  delay(1000);

  tft.loadFont("Apple-Chancery-24");
  // Show all characters on screen with 2 second (2000ms) delay between screens
  tft.showFont(2000); // Note: This function moves the cursor position!

  tft.setTextColor(TFT_RED,TFT_BLACK);
  tft.setCursor(0,0);

  tft.println("Konnichiwa");
  tft.println("Sayonara");
  tft.println();
  tft.unloadFont();

  tft.loadFont("Latin-Hiragana-24");
  tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.println("こんにちは");
  tft.println("さようなら");
  tft.unloadFont();
  
}
void loop(){}
