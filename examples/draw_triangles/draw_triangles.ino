
#include <SoftwareSerial.h>
#include <Warefab_TFT.h>


SoftwareSerial ss_tft(2, 3); // RX, TX
Warefab_TFT tft(&ss_tft);

void setup() {
  //initialize uart speed, 115200
  tft.begin(115200);
  //clear screen
  tft.clearScreen();
  delay(1000);
  //set brush color, fill color
  tft.brushColor(255, 0, 0);
  //set pen color
  tft.penColor(0, 255, 0);
  delay(20);
}

void loop() {
  //draw triangles
  for (int y = 0; y < 30; y++)
  {
    for (int x = 0; x < 11; x++)
    {
      if (x % 2) tft.fillTriangle(20 + 20 * x, 10 + y * 10, 10 + x * 20,
                                    20 + y * 10, 30 + x * 20, 20 + y * 10);
      else tft.drawTriangle(20 + 20 * x, 10 + y * 10, 10 + x * 20,
                              20 + y * 10, 30 + x * 20, 20 + y * 10);
    }
    delay(20);
  }
  //delay for 5 sec before clear screen
  delay(5000);
}
