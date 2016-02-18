/*
  Warefab_TFT demo example
  Created: 10/16/2015 05:23:53
  Author: Muchiri John
*/

#include <SoftwareSerial.h>
#include <Warefab_TFT.h>

int xPos = 0;
int xpo = 0;
char ch[5];

SoftwareSerial ss_tft(2, 3); // RX, TX
Warefab_TFT tft(&ss_tft);

int ypo = tft.height;

void setup() {
  tft.begin(115200);
  tft.fillScreen(0, 0, 0);
  tft.rotateDisplay(tft.rotate.rotate_270);
  tft.penColor(250, 180, 10);
  tft.textBackColor(0, 0, 0);
  tft.setFont(tft.font.terminal);
  tft.drawText("ANALOG A0", 120, 4);
}

void loop() {
  // read the sensor and map it to the screen height
  int sensor = analogRead(A0);
  int drawHeight = map(sensor, 0, 1023, 10, tft.height - 60);

  // print out the height to the serial monitor
  //Serial.println(drawHeight);

  // draw a line in a nice color
  //tft.drawLine(xPos, tft.height - 10, xPos, tft.height - drawHeight);
  tft.drawLine(xpo, ypo, xPos, 240 - drawHeight);
  xpo = xPos;
  ypo = tft.height - drawHeight;

  sprintf(ch, "%04d", sensor);
  tft.penColor(10, 180, 250);
  tft.drawText(ch, 140, 40);
  tft.penColor(250, 180, 10);
  // if the graph has reached the screen edge
  // erase the screen and start again
  if (xPos >= tft.width) {
    xPos = xpo = 0;
    tft.fillScreen(0, 0, 0);
    tft.drawText("ANALOG A0", 120, 4);
  }
  else {
    // increment the horizontal position:
    xPos++;
  }

  delay(20);
}
