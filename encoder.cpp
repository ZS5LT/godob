#include <stdlib.h>
#include <Wire.h>
#include <HardwareSerial.h>
#include "encoder.h"

/* errors:
 *  0: None
 *  1: Data too long
 *  2: Addr NACK
 *  3: Data NACK
 *  4: Other
 *  5: Data too short
 *  6: Reg addr wr error
 *  7: Magnet error
*/

#define MAX_ENC_VAL 16383
#define NFilter 1

Encoder::Encoder(uint8_t addr)
{
  encAddr = addr;
  errno = 0;
  reset();
  enc_reverse=0;
  filter = new rfilter(NFilter,MAX_ENC_VAL+1);
}

int Encoder::readpos(void)
{
  int i, n, p;
  unsigned q;

  errno=0;
  Wire.beginTransmission(encAddr);
  /* request data from register 0xfa onwards */
  if(Wire.write(0xfa+1)<1){             // WEIRD!!! register addr Adding 1 helps for some reason !?
    errno = 6;
  }
  // Maybe some weird mismatch between arduino and ams i2c implementation?
  errno+=Wire.endTransmission()<<4; /* store endTramsmission errors in high nibble */

  if(errno)return errno;
  
  n=Wire.requestFrom(encAddr,6);
  if(n<6){
    errno = 5;
    return errno;
  }
  else if(n>6){
    errno = 1;
    return errno;
  }

  for(i=0;Wire.available();i++){
    data[i] = Wire.read();
  }

  if(n<6){
    errno = 5;
    return errno;
  }
  else if(n>6){
    errno = 1;
    return errno;
  }

  if(data[1] != 1){
    errno = 7;
    return errno;
  }

  q = (data[4]<<6) | (data[5]&0x3f);
  if(enc_reverse){
    q = MAX_ENC_VAL - q;
  }

  //rawpos = q;
  rawpos = filter->inout(q);
  p = rawpos - zeropos;
  if(p<0)p+=MAX_ENC_VAL+1;
  position = p;
  return 0;
}

int Encoder::lasterr(void)
{
  return errno;
}

void Encoder::reset(void)
{
  int i;
  for(i=0;i<NFilter;i++){
    readpos();
  }
  zeropos = rawpos;
}

void Encoder::reverse(int en)
{
  enc_reverse = en;
}

int Encoder::lastpos(void)
{
  return position;
}

void Encoder::set(int pos)
{
  int zp;
  readpos();
  zp = rawpos - pos;
  if(zp<0)zp+=MAX_ENC_VAL+1;
  zeropos = zp;
}
