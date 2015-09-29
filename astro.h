#ifndef ASTRO_H
#define ASTRO_H

typedef struct{
  float RA;
  float dec;
  float az;
  float alt;
  float LST;
}starpos_s;

class Astro{
 public:
  Astro(void);
  Astro(HardwareSerial *serial);
  float get_LST(time_t ts);
  time_t get_LT(float lst);
  void eq_to_horz(starpos_s &sp);
  void horz_to_eq(starpos_s &sp);
  float last_latitude(void);
  float last_longitude(void);
  float latitude1(starpos_s &s1);
  float latitude2(starpos_s &s1, starpos_s &s2);
  void dump(void);
  
 private:
  static time_t j2k_t;
  static HardwareSerial *Serial;
  float LAT,LON,TLocal;
  int TZone;
};

#endif
