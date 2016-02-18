/*
  Warefab_TFT demo example
  Created: 10/16/2015 05:23:53
  Author: Muchiri John
*/

#include <SoftwareSerial.h>
#include <Warefab_TFT.h>

uint16_t xpb = 0;
uint16_t ypb = 0;
uint16_t pxpos = 0;
uint16_t pypos = 0;
int pir = 0;
char brg[5];
uint8_t count = 100;

SoftwareSerial ss_tft(2, 3); // RX, TX
Warefab_TFT tft(&ss_tft);


void setup() {
  tft.begin(115200);
  tft.setBrightness(count);
  //colors
  tft.fillScreen(0, 0, 0);
  tft.textBackColor(0, 0, 0);
  tft.penColor(250, 250, 250);
  //oi
  tft.setFont(tft.font.terminal);
  //rotate 0
  tft.rotateDisplay(tft.rotate.rotate_0);
  //buttons
  tft.drawRectangle(10, 250, 115, 300, 1);
  tft.drawRectangle(120, 250, 230, 300, 1);
  //headers
  //font
  tft.setFont(tft.font.terminal);
  tft.penColor(255, 0, 0);
  tft.drawText("UP",  50 , 270);
  tft.penColor(0, 255, 0);
  tft.drawText("DOWN", 150 , 270);
  tft.penColor(255, 255, 0);

  tft.drawText("BRIGHTNESS", 60, 90);
  tft.penColor(0, 255, 255);
  tft.drawText("%", 165, 130);
  //font
  tft.setFont(tft.font.elephant);
  //loop
  //itoa(count, brg, 10);
  sprintf(brg, "%03d", count);
  tft.drawText(brg, 65, 120);
}

void loop() {
  // put your main code here, to run repeatedly:
  //get sensor data
  if (tft.getSensorData()) {
    //get touch x and y pos
    xpb = tft.touchX;
    ypb = tft.touchY;

    //draw coordinates
    //itoa(count, brg, 10);
    sprintf(brg, "%03d", count);
    tft.drawText(brg, 65, 120);
    //increase brightness button
    if (((xpb > 169 && xpb < 488) && (ypb > 746 && ypb < 898))/* ||
        (tft.irCode == 0x4BB0)*/) {
      if (count < 100) {
        count += 1;
        tft.setBrightness(count);
      }
    }
    //decrease brightness button
    else if (((xpb > 532 && xpb < 875) && (ypb > 746 && ypb < 898))/* ||
             (tft.irCode == 0x5BA0)*/) {
      if (count > 0) {
        count -= 1;
        tft.setBrightness(count);
      }
    }
    //delay for 50 ms
    delay(50);
  }
}
