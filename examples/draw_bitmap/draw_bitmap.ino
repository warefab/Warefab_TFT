
#include <SoftwareSerial.h>
#include <Warefab_TFT.h>
#include "images.h"

char deg[3];
int y = 0;


SoftwareSerial ss_tft(2, 3); // RX, TX
Warefab_TFT tft(&ss_tft);

void setup() {
  //initialize uart speed, 115200
  tft.begin(115200);
  //clear display
  tft.clearScreen();
  //rotate display, normal view
  tft.rotateDisplay(tft.rotate.rotate_0);
  //set pen color, rgb values
  tft.penColor(0, 255, 255);
  //set brush color, rgb values
  tft.brushColor(0, 0, 0);
  tft.setFont(tft.font.peanut);
  delay(50);
  //draw icon 1
  tft.drawBitmap(20, 50, earphones, 48, 48, 288);
  tft.drawText("AUDIO", 25, 100);
  delay(20);
  tft.penColor(255, 255, 0);
  delay(10);
  //draw icon 2
  tft.drawBitmap(100, 50, bulb, 48, 48, 288);
  tft.drawText("BULB", 105, 100);
  delay(20);
  tft.penColor(0, 255, 0);
  delay(10);
  //draw icon 3
  tft.drawBitmap(180, 50, on_off, 48, 48, 288);
  tft.drawText("SWITCH", 180, 100);
  delay(20);
  tft.penColor(255, 0, 0);
  delay(10);
  //draw icon 3
  tft.drawBitmap(20, 130, colors, 48, 48, 288);
  tft.drawText("COLOUR", 20, 180);
  delay(20);
  tft.penColor(0, 0, 255);
  delay(10);
  //draw icon 3
  tft.drawBitmap(100, 130, code, 48, 48, 288);
  tft.drawText("CODE", 105, 180);
  delay(20);
  tft.penColor(255, 0, 255);
  delay(10);
  //draw icon 3
  tft.drawBitmap(180, 130, call, 48, 48, 288);
  tft.drawText("CALL", 185, 180);
  delay(20);
  tft.penColor(255, 255, 255);
  delay(10);
  //draw icon 3
  tft.drawBitmap(20, 210, phone, 48, 48, 288);
  tft.drawText("PHONE", 25, 260);
  delay(20);
  tft.penColor(55, 255, 55);
  delay(10);
  //draw icon 3
  tft.drawBitmap(100, 210, settings, 48, 48, 288);
  tft.drawText("SETTINGS", 90, 260);
  delay(20);
  tft.penColor(0, 255, 255);
  delay(10);
  //draw icon 3
  tft.drawBitmap(180, 210, record, 48, 48, 288);
  tft.drawText("RECORD", 180, 260);
}

void loop() {
    }
