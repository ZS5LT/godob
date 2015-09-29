#include "buttons.h"

uint8_t Buttons::kpin;
bool Buttons::pending = false;;
btnval_e Buttons::keyno, Buttons::keystatus = btnNONE;

Buttons::Buttons(int keypin)
{
  kpin = keypin;
}

bool Buttons::poll(void)
{
  const uint8_t wait=5;
  static uint8_t stab=0;
  btnval_e newkey = read_LCD_buttons();
  if(newkey != btnNONE){
    if(newkey != keystatus){
      pending = true;
      keyno = newkey;
      stab = 0;
    }
    else if(stab>=wait){
      pending = true;
    }
    if(stab<wait){
      stab++;
    }
  }
  keystatus = newkey;
  return pending;
}

bool Buttons::gotkey(void)
{
  return pending;
}

btnval_e Buttons::lastkey(void)
{
  pending = false;
  return keyno;
}

btnval_e Buttons::read_LCD_buttons(void)
{
 int adc_key_in = analogRead(0);      // read the value from the sensor 
 // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
 // we add approx 50 to those values and check to see if we are close
 if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
 // For V1.1 us this threshold
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 250)  return btnUP; 
 if (adc_key_in < 450)  return btnDOWN; 
 if (adc_key_in < 650)  return btnLEFT; 
 if (adc_key_in < 850)  return btnSELECT;  
}
