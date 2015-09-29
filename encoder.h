#ifndef ENCODER_H
#define ENCODER_h

class Encoder
{
 public:
  Encoder(uint8_t addr);
  int readpos(void);
  int lasterr(void);
  int lastpos(void);
  void reset(void);
  void set(int pos);
  void reverse(int en);
  
 private:
  int encAddr;
  int errno;
  unsigned position;
  uint8_t data[8];
  unsigned zeropos;
  int enc_reverse;

};


#endif
