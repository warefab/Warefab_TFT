/*
  Warefab_TFT demo example
  Created: 10/16/2015 05:23:53
  Author: Muchiri John
*/

#include <SoftwareSerial.h>
#include <Warefab_TFT.h>

char deg[3];
int y = 0;

SoftwareSerial ss_tft(2, 3); // RX, TX
Warefab_TFT tft(&ss_tft);

void setup() {
  tft.begin(115200);
  // put your setup code here, to run once:
  tft.clearScreen();
  tft.penColor(0, 255, 255);
  tft.brushColor(0, 0, 0);
  tft.setFont(tft.font.peanut);
  //tft.fillCircle(120, 160, 45);
  tft.drawCircle(120, 160, 38);
  tft.drawCircle(120, 160, 45);
  delay(30);
}

void loop() {
  // put your main code here, to run repeatedly:
  tft.brushColor(random(10, 255), random(10, 255), random(10, 255));
  //draw arc 0-360 deg
  for (int x = 0; x <= 360; x += 5)
  {
    tft.drawArc(120, 160, y, x, 40, 4);
    sprintf(deg, "%03d", x);
    tft.drawText(deg, 110, 155);
    delay(20);
    if (x > 0) y = x - 5;
  }
  delay(2000);
  //draw arc 360-0 deg
  tft.brushColor(0, 0, 0);
  for (int x = 360; x >= 0; x -= 5)
  {
    if (x > 0) y = x - 5;
    tft.drawArc(120, 160, y, x, 40, 4);
    sprintf(deg, "%03d", x);
    tft.drawText(deg, 110, 155);
    delay(20);
  }
  delay(2000);
}
