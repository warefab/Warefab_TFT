/*
   Warefab_TFT.h

   Created: 13/02/2016 05:23:37
   Author: Muchiri John
*/
#ifndef WAREFAB_TFT_H_
#define WAREFAB_TFT_H_

#include <Arduino.h>
#include <avr/pgmspace.h>

#define use_ss

#ifdef use_ss
#include <SoftwareSerial.h>
#endif
//swap
#define swap(a,b) ((uint16_t n = b); b = a; a = n;)
//fonts struct
typedef struct {
  static const char terminal = 'i';
  static const char ocr      = 'c';
  static const char peanut   = 'd';
  static const char comic    = 'o';
  static const char calibri  = 'f';
  //char consolas = 'g';
  //char droid    = 's';
  static const char elephant = 'h';
  static const char atomic   = 'a';
  static const char icon   = 'p';
  static const char icon_l = 'q';
} Font;
//rotation struct
typedef struct {
  static const char rotate_0   = 'p';
  static const char rotate_90  = 'i';
  static const char rotate_180 = 'q';
  static const char rotate_270 = 'n';
} Rotate;
//class
class Warefab_TFT
{
  public:
#ifdef use_ss
    Warefab_TFT(SoftwareSerial *ss);
#else
    Warefab_TFT(HardwareSerial *hs);
#endif
    void begin(unsigned long int ts = 115200, uint8_t rst = 1);
    void uartSpeed(unsigned int bd = 115200);
    void drawPixel(uint16_t x, uint16_t y);
    void setFont(char fnt = 'i');
    void drawChar(uint8_t c, uint16_t x, uint16_t y);
    void drawText(char *s, uint16_t x, uint16_t y);
    void penColor(uint8_t r, uint8_t g, uint8_t b);
    void brushColor(uint8_t r, uint8_t g, uint8_t b);
    void textBackColor(uint8_t r, uint8_t g, uint8_t b);
    void fillScreen(uint8_t r, uint8_t g, uint8_t b);
    void clearScreen();
    void drawCircle(uint16_t x1, uint16_t y1, uint16_t r);
    void fillCircle(uint16_t x1, uint16_t y1, uint16_t r);
    void drawEllipse(uint16_t x1, uint16_t y1, uint16_t xr, uint16_t yr);
    void fillEllipse(uint16_t x1, uint16_t y1, uint16_t xr, uint16_t yr);
    void drawArc( uint16_t x0, uint16_t y0, uint16_t s, uint16_t e,
                  uint8_t r, uint8_t th);
    void drawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
                       uint8_t type = 0);
    void fillRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
                       uint8_t type = 0);
    void drawTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,
                      uint16_t x2, uint16_t y2);
    void fillTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,
                      uint16_t x2, uint16_t y2);
    void drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
    void drawVHLine(uint16_t x1, uint16_t y1, uint16_t ln, uint8_t tp = 0);
    uint8_t getSensorData();
    void drawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h,
                   unsigned int *image, unsigned int len);
    void drawBitmap(uint16_t x, uint16_t y, const uint8_t *bitmap,
                    uint16_t w, uint16_t h, uint16_t len);
    void setBrightness(uint8_t b);
    void rotateDisplay(char rt = 'p');
    void power(uint8_t st);
    void reset();

    Font font;
    Rotate rotate;

    uint16_t touchX;
    uint16_t touchY;
    uint16_t irCode;

    uint16_t height;
    uint16_t width;

  private:
#ifdef use_ss
    SoftwareSerial *tft_serial;
#else
    HardwareSerial *tft_serial;
#endif

    char rot;
    //uint16_t touch_coords[4];
    uint8_t sensor_data[15];
    char cmd[50], *p;
    inline void sensorEval(char *);
    void setColorHelper(uint8_t c, uint8_t r, uint8_t g, uint8_t b);
    inline void sendHelper(char *);

    uint8_t index;
    double c_time;
    double p_time;
    char sdata[15];
    uint8_t sc;
};

#endif /* WAREFAB_TFT_H_ */
