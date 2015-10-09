#include <stdlib.h>
#include <HardwareSerial.h>
#include "rfilter.h"

int rfilter::instx = 0;

rfilter::rfilter(int depth, int range)
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
}

int rfilter::inout(int x)
{
  int s,r,d;
  if(rdepth < 2){
    acc = x;
  }
  else{
    s = x;
    r = acc/rdepth;
    d = s - r;
    if(d > rrange/4)s-=rrange;
    if(d <= -(rrange/4))s+=rrange;
    acc -= rbuffer[wrpos];
    acc += s;
    rbuffer[wrpos++] = s;
    wrpos %= rdepth;
  }

  if(r<0)rshift(rrange);
  if(r>rrange/2*3)rshift(-rrange);

  if(r>=rrange)r-=rrange;

  return r;
}

inline int rfilter::output(void)
{
  return acc/rdepth;
}

void rfilter::rshift(int d)
{
  int i;
  for(i=0;i<rdepth;i++){
    rbuffer[i] += d;
    acc += d;
  }
}
