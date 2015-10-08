#ifndef ASTRO_H
#define ASTRO_H

typedef struct{
  float RA;
  float dec;
  float az;
  float alt;
  float GMST;
}starpos_s;

class Astro{
 public:
  Astro(void);
  float get_GMST(time_t ts);
  time_t get_LT(float lst);
  void eq_to_horz(starpos_s &sp);
  void horz_to_eq(starpos_s &sp);
  float last_latitude(void);
  float last_longitude(void);
  float latitude1(starpos_s &s1);
  float latitude2(starpos_s &s1, starpos_s &s2);
  float horz_range(starpos_s &sp1, starpos_s &sp2);
  float eq_range(starpos_s &sp1, starpos_s &sp2);
  
 private:
  static time_t j2k_t;
  static HardwareSerial *Serial;
  float LAT,LON;
  int TZone;
};

#endif
