
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
  //set font
  tft.setFont(tft.font.peanut);
  delay(50);
  //draw icons
  drawIcons();
}

void loop() {
}

//draw icons method
void drawIcons()
{
  //draw icon 1
  tft.drawBitmap(20, 50, earphones, 48, 48, 288);
  tft.drawText("AUDIO", 25, 100);
  tft.penColor(255, 255, 0);
  delay(30);
  //draw icon 2
  tft.drawBitmap(100, 50, bulb, 48, 48, 288);
  tft.drawText("BULB", 105, 100);
  tft.penColor(0, 255, 0);
  delay(20);
  //draw icon 3
  tft.drawBitmap(180, 50, on_off, 48, 48, 288);
  tft.drawText("SWITCH", 180, 100);
  tft.penColor(255, 0, 0);
  delay(30);
  //draw icon 4
  tft.drawBitmap(20, 130, colors, 48, 48, 288);
  tft.drawText("COLOUR", 20, 180);
  tft.penColor(0, 0, 255);
  delay(20);
  //draw icon 5
  tft.drawBitmap(100, 130, code, 48, 48, 288);
  tft.drawText("CODE", 105, 180);
  tft.penColor(255, 0, 255);
  delay(30);
  //draw icon 6
  tft.drawBitmap(180, 130, call, 48, 48, 288);
  tft.drawText("CALL", 185, 180);
  tft.penColor(255, 255, 255);
  delay(20);
  //draw icon 7
  tft.drawBitmap(20, 210, message, 48, 48, 288);
  tft.drawText("MESSAGE", 15, 260);
  tft.penColor(55, 255, 55);
  delay(30);
  //draw icon 8
  tft.drawBitmap(100, 210, settings, 48, 48, 288);
  tft.drawText("SETTINGS", 90, 260);
  tft.penColor(0, 255, 255);
  delay(20);
  //draw icon 9
  tft.drawBitmap(180, 210, info, 48, 48, 288);
  tft.drawText("INFO", 185, 260);
}

