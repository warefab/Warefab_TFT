/*
  Warefab_TFT demo example
  Created: 10/16/2015 05:23:53
  Author: Muchiri John
*/

#include <SoftwareSerial.h>
#include <Warefab_TFT.h>

char data[15];

SoftwareSerial ss_tft(2, 3); // RX, TX
Warefab_TFT tft(&ss_tft);


void setup() {
  tft.begin(115200);
  Serial.begin(115200);
  tft.rotateDisplay(tft.rotate.rotate_0);
}

void loop() {
  if (tft.getSensorData()) {
    sprintf(data, "%d, %d, %X", tft.touchX, tft.touchY, tft.irCode);
    Serial.println(data);
  }
  delay(100);
}
