/*
  Warefab_TFT demo example
  Created: 10/16/2015 05:23:53
  Author: Muchiri John
*/

#include <SoftwareSerial.h>
#include <Warefab_TFT.h>

char ch_ir[5];

SoftwareSerial ss_tft(2, 3); // RX, TX
Warefab_TFT tft(&ss_tft);


void setup() {
  tft.begin(115200);
  tft.fillScreen(0, 0, 0);
  tft.rotateDisplay(tft.rotate.rotate_0);
  tft.penColor(255, 255, 0);
  tft.textBackColor(0, 0, 0);
  tft.setFont();
  tft.drawText("IR CODE", 70, 90);
  delay(10);
}

void loop() {
  if (tft.getSensorData() && (tft.irCode > 0)) {
    memset(ch_ir, 0, 5);
    sprintf(ch_ir, "%X", tft.irCode);
    tft.drawText(ch_ir, 80, 120);
    delay(50);
  }
}
