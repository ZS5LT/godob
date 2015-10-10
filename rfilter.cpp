#include <stdlib.h>
#include <HardwareSerial.h>
#include "rfilter.h"

int rfilter::instx = 0;

/* average over n=depth values, where 0 <= values <= range.
   Add obits oversampled bits to the output signal
*/
rfilter::rfilter(int depth, int range, int obits)
{
  int i;
  inst = instx++;
  rdepth = depth;
  rbuffer = (int *)malloc(rdepth * sizeof(int));
  if(!rbuffer){
    rdepth = 1;
  }
  else{
    for(i=0;i<rdepth;i++){
      rbuffer[i]=0;
    }
  }
  acc = 0;
  wrpos = 0;
  rrange = range;
  this->obits = obits;
}

int rfilter::inout(int x)
{
  int s,d;
  long r;
  if(rdepth < 2){
    acc = x>>obits;
  }
  else{
    s = x;
    r = acc/rdepth;
    d = s - r;
    if(d > rrange/2)s-=rrange;
    if(d <= -(rrange/2))s+=rrange;
    acc -= rbuffer[wrpos];
    acc += s;
    rbuffer[wrpos++] = s;
    wrpos %= rdepth;
  }

  if(r<0)rshift(rrange);
  if(r>rrange/2*3)rshift(-rrange);

  r = acc/(rdepth>>obits);
  if(r>=(long)rrange<<obits)r-=(long)rrange<<obits;

  return r;
}

inline int rfilter::output(void)
{
  return acc/(rdepth>>obits);
}

void rfilter::rshift(int d)
{
  int i;
  for(i=0;i<rdepth;i++){
    rbuffer[i] += d;
    acc += d;
  }
}
