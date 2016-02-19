/*
   Warefab_TFT.h

   Created: 13/02/2016 05:23:37
   Author: Muchiri John
*/
#include <Arduino.h>
#include <avr/pgmspace.h>

#ifdef use_ss
#include <SoftwareSerial.h>
#endif
#include "Warefab_TFT.h"

//////////////////////////////////////////////////////////////////////////
//init
//////////////////////////////////////////////////////////////////////////
#ifdef use_ss
Warefab_TFT::Warefab_TFT(SoftwareSerial *ss): irCode(0),
  touchX(0), touchY(0), height(320), width(240),
  rot('p')
{
  tft_serial = ss;
#else
Warefab_TFT::Warefab_TFT(HardwareSerial *hs) : irCode(0),
  touchX(0), touchY(0), height(320), width(240),
  rot('p')
{
  tft_serial = hs;
#endif

  memset(cmd, 0, 50);
  index = 0;
  c_time = 1000;
  p_time = 0;
  sc = 0;
  memset(sdata, 0, 15);
}
//init/begin
void Warefab_TFT::begin(unsigned long int ts, uint8_t rst)
{
  tft_serial->begin(ts);
  delay(100);
  if (rst)
  {
    reset(); //soft reset
    delay(1000);
  }

}
//uart baudRate
void Warefab_TFT::uartSpeed(unsigned int bd)
{
  sprintf(cmd, "[A3,%d]", bd);
  sendHelper(cmd);
}
//soft reset
void Warefab_TFT::reset()
{
  tft_serial->write("[e6]");
  delay(500);
}
//send to tft helper
inline void Warefab_TFT::sendHelper(char *tk)
{
  tft_serial->write(tk);
  memset(cmd, 0, 50);
}
//draw pixel
void Warefab_TFT::drawPixel(uint16_t x, uint16_t y)
{
  sprintf(cmd, "[A2,%d,%d]", x, y);
  sendHelper(cmd);
}
//draw char
void Warefab_TFT::drawChar(uint8_t c, uint16_t x, uint16_t y)
{
  sprintf(cmd, "[C4,%d,%d,%d]", c, x, y);
  sendHelper(cmd);
}
//draw text
void Warefab_TFT::drawText(char *s, uint16_t x, uint16_t y)
{
  sprintf(cmd, "[A6,%d,%d,%s]", x, y, s);
  sendHelper(cmd);
}
//set color helper
void Warefab_TFT::setColorHelper(uint8_t c, uint8_t r, uint8_t g, uint8_t b)
{
  sprintf(cmd, "[%X,%d,%d,%d]", c, r, g, b);
  sendHelper(cmd);
}
//pen color
void Warefab_TFT::penColor(uint8_t r, uint8_t g, uint8_t b)
{
  setColorHelper(0xA7, r, g, b);
}
//brush color
void Warefab_TFT::brushColor(uint8_t r, uint8_t g, uint8_t b)
{
  setColorHelper(0x9A, r, g, b);
}
//text back  color
void Warefab_TFT::textBackColor(uint8_t r, uint8_t g, uint8_t b)
{
  setColorHelper(0xA8, r, g, b);
}
//pen color
void Warefab_TFT::fillScreen(uint8_t r, uint8_t g, uint8_t b)
{
  setColorHelper(0xA9, r, g, b);
}
//clear screen
void Warefab_TFT::clearScreen()
{
  tft_serial->print("[A5,c]");
}
//draw ellipse
void Warefab_TFT::drawEllipse(uint16_t x1, uint16_t y1, uint16_t xr, uint16_t yr)
{
  sprintf(cmd, "[B9,%d,%d,%d,%d]", x1, y1, xr, yr);
  sendHelper(cmd);
}
//fill ellipse
void Warefab_TFT::fillEllipse(uint16_t x1, uint16_t y1, uint16_t xr, uint16_t yr)
{
  sprintf(cmd, "[C0,%d,%d,%d,%d]", x1, y1, xr, yr);
  sendHelper(cmd);
}
//draw circle
void Warefab_TFT::drawCircle(uint16_t x1, uint16_t y1, uint16_t r)
{
  sprintf(cmd, "[B8,%d,%d,%d]", x1, y1, r);
  sendHelper(cmd);
}
//draw arc
void Warefab_TFT::drawArc( uint16_t x0, uint16_t y0, uint16_t s, uint16_t e, uint8_t r, uint8_t th)
{
  sprintf(cmd, "[C6,%d,%d,%d,%d,%d,%d]", x0, y0, s, e, r, th);
  sendHelper(cmd);
}
//fill circle
void Warefab_TFT::fillCircle(uint16_t x1, uint16_t y1, uint16_t r)
{
  sprintf(cmd, "[B7,%d,%d,%d]", x1, y1, r);
  sendHelper(cmd);
}
//draw rectangle, normal and round
void Warefab_TFT::drawRectangle(uint16_t x1, uint16_t y1, uint16_t x2,
                                uint16_t y2, uint8_t type)
{
  (type == 0) ? type = 0xB2 : type = 0xB4;
  sprintf(cmd, "[%X,%d,%d,%d,%d]", type, x1, y1, x2, y2);
  sendHelper(cmd);
}
//fill rectangle, normal and round
void Warefab_TFT::fillRectangle(uint16_t x1, uint16_t y1, uint16_t x2,
                                uint16_t y2, uint8_t type)
{
  (type == 0) ? type = 0xB1 : type = 0xB3;
  sprintf(cmd, "[%X,%d,%d,%d,%d]", type, x1, y1, x2, y2);
  sendHelper(cmd);
}
//draw triangle
void Warefab_TFT::drawTriangle(uint16_t x0, uint16_t y0, uint16_t x1,
                               uint16_t y1, uint16_t x2, uint16_t y2)
{
  sprintf(cmd, "[C2,%d,%d,%d,%d,%d,%d]", x0, y0, x1, y1, x2, y2);
  sendHelper(cmd);
}
//filltriangle
void Warefab_TFT::fillTriangle(uint16_t x0, uint16_t y0, uint16_t x1,
                               uint16_t y1, uint16_t x2, uint16_t y2)
{
  sprintf(cmd, "[C3,%d,%d,%d,%d,%d,%d]", x0, y0, x1, y1, x2, y2);
  sendHelper(cmd);
}
//fill rectangle, normal and round
void Warefab_TFT::drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
  //(type == 0) ? type = 0xB5 : type = 0xB3;
  sprintf(cmd, "[B5,%d,%d,%d,%d]", x1, y1, x2, y2);
  sendHelper(cmd);
}
//draw vertical/horizontal line
void Warefab_TFT::drawVHLine(uint16_t x1, uint16_t y1, uint16_t ln, uint8_t tp)
{
  sprintf(cmd, "[B6,%d,%d,%d,%d]", x1, y1, ln, tp);
  sendHelper(cmd);
}
//change font
void Warefab_TFT::setFont(char fnt)
{
  sprintf(cmd, "[C1,%c]", fnt);
  sendHelper(cmd);
}
//get sensor data
uint8_t Warefab_TFT::getSensorData()
{
  for (int x = 0; x < 5; x++) {
    sc = 0;
    tft_serial->print("[e0]");
    while ((millis() - p_time) <= c_time)
    {
      if (tft_serial->available() > 0)
      {
        unsigned char bt = (unsigned char)tft_serial->read();
        if (bt == '[')
        {
          index = 0;
          memset(sdata, 0, 15);
        }
        else if (bt == ']')
        {
          sc = 1;
          x = 5;
          break;
        } else
        {
          sdata[index++] = bt;
        }
      }
    }
    p_time = millis();
  }

  if (sc) {
    sensorEval(sdata);
  } else
  {
    touchX = touchY = irCode = 0;
  }

  return sc;
}
//sensor eval
inline void Warefab_TFT::sensorEval(char *dt)
{
  if (rot == 'p' || rot == 'q') {
    touchX = atoi(strtok((char *)dt, ","));
    touchY = atoi(strtok(NULL, ","));
  } else {
    touchY = atoi(strtok((char *)dt, ","));
    touchX = atoi(strtok(NULL, ","));
  }
  irCode = strtol(strtok(NULL, ","), NULL, 16);
}
//show image
void Warefab_TFT::drawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, unsigned int *image, unsigned int len)
{
  sprintf(cmd, "[A0,%d,%d,%d,%d,%d]", x, y, h, w, len);
  sendHelper(cmd);
  delay(20);
  for (int x = 0; x < len; x++)
  {
    tft_serial->write(*(image + x) & 0xff);
    tft_serial->write(*(image + x) >> 8);
  }
  delay(20);
}
//set brightness
void Warefab_TFT::setBrightness( uint8_t b)
{
  sprintf(cmd, "[E5,%d]", b);
  sendHelper(cmd);
}
//set display rotation
void Warefab_TFT::rotateDisplay(char rt)
{
  if (rt == 'p' || rt == 'q') {
    width = 240; height = 320;
  } else
  {
    width = 320; height = 240;
  }
  rot = rt;
  sprintf(cmd, "[A5,%c]", rt);
  sendHelper(cmd);
}
//power on/off
void Warefab_TFT::power(uint8_t st)
{
  char c = 'f';
  if (st) c = 'o';
  sprintf(cmd, "[A5,%c]", c);
  sendHelper(cmd);
}
//draw bitmap image
void Warefab_TFT::drawBitmap(uint16_t x, uint16_t y,
                             const uint8_t *bitmap, uint16_t w, uint16_t h, uint16_t len)
{
  sprintf(cmd, "[C5,%d,%d,%d,%d,%d]", x, y, w, h, len);
  sendHelper(cmd);
  delay(20);
  for (int x = 0; x < len; x++)
  {
    tft_serial->write((uint8_t)pgm_read_byte(bitmap + x));
  }
  delay(20);
}
