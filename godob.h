#ifndef GODOB_H
#define GODOB_H

#include <Time.h>
#include <DS1302RTC.h>
#include <LiquidCrystal.h>
#include <Arduino.h>
#include "buttons.h"
#include "encoder.h"
#include "astro.h"

typedef enum{  /* status display modes */
/* local time, local siderial time, lat/long, alt/az, ra/dec */
  ds_time=0, ds_lst, ds_loc, ds_horz, ds_eq, ds_targ, ds_last
}dstat_e;

class godob
{
 public:
  godob(uint8_t tCE, uint8_t tIO, uint8_t tCLK,
	 uint8_t dRS, uint8_t dE, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, uint8_t dBL);
  void begin(void);
  void run(void);
  void print(char *str);
  void println(char *str);

 private:
  static uint8_t pin_tCE;
  static uint8_t pin_tIO;
  static uint8_t pin_tCLK;
  static uint8_t pin_dRS;
  static uint8_t pin_dE;
  static uint8_t pin_d4;
  static uint8_t pin_d5;
  static uint8_t pin_d6;
  static uint8_t pin_d7;
  static uint8_t pin_BL;

  static int Backlight;
  uint8_t t_idx;
  long t_adjust;
  bool t_set;
  dstat_e dstat;
  bool Connected;
  time_t connect_time;
  starpos_s star[2];
  int stars;
  bool reqPending;

  static DS1302RTC *RTC;
  static LiquidCrystal *LCD;
  static Buttons *BTN;
  static Encoder *ENCAlt;
  static Encoder *ENCAz;
  static Astro *AST;

  void printtime(void);
  void printdate(void);
  void printndigits(char pad, char len, int number);
  void print2digits(int k);
  void handle_time_keys(btnval_e lcd_key);
  void handle_main_keys(btnval_e lcd_key);
  long show_adjust(uint8_t xidx);
  void setRTC(void);
  void show_radec(void);
  void show_altaz(void);
  void show_rad(float rad);
  void show_hms(double rad);
  void show_dms(float rad);
  void handle_serial(void);
  void print_quad(unsigned u);
  unsigned read_quad(void);
  int parse_hex(char c);
  void LCDBrightness(int d);
  };

#endif
