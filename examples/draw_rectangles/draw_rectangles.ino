
#include <SoftwareSerial.h>
#include <Warefab_TFT.h>

int x, y, r, g, b;

SoftwareSerial ss_tft(2, 3); // RX, TX
Warefab_TFT tft(&ss_tft);

void setup() {
  //initialize uart speed, 115200
  tft.begin(115200);
}

void loop() {
  //draw rectangles
  drawRects();
}

void drawRects()
{
  //initialize colors
  tft.fillScreen(255, 255, 255);
  //rotate 90 degrees
  tft.rotateDisplay(tft.rotate.rotate_90);
  //delay for 5ms
  delay(5);
  //loop drawing random rectangles
  for (uint8_t i = 0; i < 50 ; i++) {
    //random pen color
    r = random(0, 255);
    g = random(0, 255);
    b = random(0, 255);
    tft.brushColor(r, g, b);
    //draw fill round rectangle of random sizer
    tft.fillRectangle(x, y, (x + random(5, 41)), (y + random(5, 41)), 0);
    //set a random position
    x = random(20, 301);
    y = random(20, 221);
    //animate drawing with a 100 ms delay
    delay(50);
  }
}

