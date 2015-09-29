#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>

typedef enum{
  btnRIGHT=0,
  btnUP,
  btnDOWN,
  btnLEFT,
  btnSELECT,
  btnNONE
}btnval_e;


class Buttons
{
 public:
  Buttons(int keypin);
  bool poll(void);
  bool gotkey(void);
  btnval_e lastkey(void);

 private:
  static uint8_t kpin;
  static bool pending;
  static btnval_e keyno;
  static btnval_e keystatus;
  
  btnval_e read_LCD_buttons(void);
};

#endif
