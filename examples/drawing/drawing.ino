/*
  Warefab_TFT demo example
  Created: 10/16/2015 05:23:53
  Author: Muchiri John
*/

#include <SoftwareSerial.h>
#include <Warefab_TFT.h>

int tsx, tsy;

SoftwareSerial ss_tft(2, 3); // RX, TX
Warefab_TFT tft(&ss_tft);


void setup() {
  tft.begin(115200);
  tft.fillScreen(15, 167, 255);
  tft.rotateDisplay(tft.rotate.rotate_0);
  tft.penColor(255, 255, 255);
  tft.fillRectangle(0, 0 , 239, 285);
  tft.textBackColor(15, 167, 255);
  tft.setFont(tft.font.terminal);
  tft.drawText("CLEAR", 80, 295);
  delay(10);
}

void loop() {
  if (tft.getSensorData()) {

    tft.penColor(random(10, 255), random(10, 255), random(10, 255));
    if (!(tft.touchX < 50 && tft.touchX < 50 && tft.irCode == 0)){

    tsx = uint16_t(map(tft.touchX, 120, 898, 0, 239));
    tsy = uint16_t(map(tft.touchY, 55, 950, 0, 319));

    if (tsy > 300) {
      tft.penColor(255, 255, 255);
      tft.fillRectangle(0, 0 , 239, 285);
    }
    else
      tft.fillCircle(tsx, tsy, 4);
    }
    delay(100);
  }
}
