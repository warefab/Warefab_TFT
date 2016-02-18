/*
  Warefab_TFT demo example
  Created: 10/16/2015 05:23:53
  Author: Muchiri John
*/

#include <SoftwareSerial.h>
#include <Warefab_TFT.h>

char c[2];

SoftwareSerial ss_tft(2, 3); // RX, TX
Warefab_TFT tft(&ss_tft);

void setup() {
  tft.begin(115200);
  tft.fillScreen(0, 0, 0);
  tft.textBackColor(0, 0, 0);
  tft.penColor(250, 0, 250);
  tft.setFont(tft.font.icon_l);
}

void loop() {
  for (uint8_t x = 32; x <= 41; x++)
  {
    sprintf(c, "%c", (char)(x));
    tft.drawText(c, 50, 50);
    delay(1000);
  }
}
