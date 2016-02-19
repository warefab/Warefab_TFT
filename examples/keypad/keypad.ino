#include <SoftwareSerial.h>
#include <Warefab_TFT.h>

char buttons[12] = {
  '1', '2', '3',
  '4', '5', '6',
  '7', '8', '9',
  '*', '0', 'C'
};
//button coordinates
uint16_t button_coords[13][5];

//selection
char selection = ' ';
//index
uint16_t index = 0;
//xpos
uint16_t xpos = 5;
//ypos
uint16_t ypos = 80;
char cstr[30];
char pwd[5] = {0, 0, 0, 0, 0};
char actual[4] = {'4', '3', '4', '5'};
uint8_t pindex = 0;
uint8_t scs = 0;

SoftwareSerial ss_tft(2, 3); // RX, TX
Warefab_TFT tft(&ss_tft);


void setup() {
  //initialize uart speed, 115200
  tft.begin(115200);
  __init();
}

void loop() {
  // put your main code here, to run repeatedly:
  checkButton();
}
//init, draw buttons and register touch coordinates
void __init()
{
  memset(cstr, 0, 30);
  //fill screen, black
  tft.fillScreen(0, 0, 0);
  //rotate display
  tft.rotateDisplay(tft.rotate.rotate_0);
  //set pen color
  tft.penColor(120, 120, 120);
  tft.brushColor(0, 0, 0);
  tft.fillRectangle(4, 30, 234, 100, 1);
  tft.setFont(tft.font.calibri);
  tft.penColor(250, 255, 10);
  tft.textBackColor(0, 0, 0);
  tft.drawText("ENTER CODE", 4, 10);
  //set font
  tft.setFont(tft.font.terminal);
  //create buttons
  for (int y = 0; y < 4; y++)
  {
    for (int x = 0; x < 3; x++)
    {
      //draw button
      tft.penColor(50, 50 , 150);
      tft.drawRectangle(58 * x + 4, 105 + 50 * y + 4, 58 * x + 58 - 2, 105 + 50 * y + 50 - 2, 1);
      tft.penColor(255, 255, 255);
      //tft.textBackColor(50, 50 , 110);
      sprintf(cstr, "%c", buttons[index]);
      tft.drawText(cstr, 58 * x + 24, 105 + 50 * y + 17);
      //register touch coordinates and button name
      uint16_t c[5] = {58 * x + 4, 105 + 50 * y + 4, 58 * x + 58 - 2, 105 + 50 * y + 50 - 2, (uint8_t)buttons[index]};
      for (uint8_t j = 0; j < 5; j++)
        button_coords[index][j] = c[j];
      index += 1;
      delay(1);
    }
  }
  //Enter button
  tft.penColor(150, 50 , 50);
  tft.drawRectangle(180, 110, 234, 302, 1);
  tft.penColor(255, 255, 255);
  //tft.textBackColor(110, 50 , 50);
  tft.drawText(">>", 195, 200);
  //loop
  tft.penColor(0, 255, 255);
  tft.setFont(tft.font.terminal);
  //tft.textBackColor(120, 120, 120);
  tft.setFont(tft.font.elephant);
  delay(20);
}
//check which button pressed
void checkButton()
{
  if (tft.getSensorData() && (tft.touchX > 20 && tft.touchY > 20)) {
    //map touch xpos to lcd(0-239)
    xpos = uint16_t(map(tft.touchX, 120, 898, 0, 239));
    //map touch ypos to lcd(0-319)
    ypos = uint16_t(map(tft.touchY, 55, 950, 0, 319));

    if ((xpos >= 180 &&  xpos <= 234 &&
         ypos >= 110 &&  ypos <= 302) /*||
        tft.irCode == irCtrlCodes[13]*/) {
      scs = 1;
      for (uint8_t x = 0; x < 4; x++)
      {
        if (pwd[x] != actual[x])
        {
          scs = 0;
          break;
        }
      }
      tft.setFont(tft.font.terminal);
      if (scs) tft.drawText("SUCCESS", 55, 60);
      else
      {
        tft.penColor(255, 0, 0);
        tft.drawText("ERROR", 55, 60);
      }
      tft.setFont(tft.font.elephant);
    } else {
      //check button touch
      for (uint8_t button = 0; button < 12; button++) {
        if ((xpos >= button_coords[button][0] &&  xpos <= button_coords[button][2] &&
             ypos >= button_coords[button][1] &&  ypos <= button_coords[button][3])/* ||
            tft.irCode == irCtrlCodes[button]*/) {
          //button item name
          selection =  button_coords[button][4];
          //set button action info
          switch (selection) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
              if (pindex < 4)
              {
                pwd[pindex] = selection;
                pwd[pindex + 1] = '\0';
                tft.drawText(pwd, 30, 40);
                pindex++;
              }
              break;
            case 'C':
              tft.brushColor(0, 0, 0);
              tft.penColor(120, 120, 120);
              tft.fillRectangle(4, 30, 234, 100, 1);
              tft.penColor(0, 255, 255);
              pindex = 0;
              memset(pwd, 0, 4);
              break;
            default:
              break;
          }
          break;
        }
      }
      delay(100);
    }
  }
}

