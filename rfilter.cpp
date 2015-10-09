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
  offset = range/2;
}

int rfilter::inout(int x)
{
  int s,r,d;
  if(rdepth < 2){
    acc = x + offset;
  }
  else{
    s = x + offset;
    r = acc/rdepth;
    d = s - r;
    if(d > rrange/2)s-=rrange;
    //if(d <= -(rrange/2))s+=rrange;
    acc -= rbuffer[wrpos];
    acc += s;
    rbuffer[wrpos++] = s;
    wrpos %= rdepth;
  }

  r = acc/rdepth - offset;

  if(inst==0){
    Serial.print(acc);
    Serial.print(" ");
    Serial.print(x);
    Serial.print(" ");
    Serial.print(s);
    Serial.print(" ");
    Serial.print(d);
    Serial.print(" ");
    Serial.println(r);
  }  
  return r;
}

inline int rfilter::output(void)
{
  return acc/rdepth - offset;
}

void rfilter::rshift(int d)
{
  int i;
  for(i=0;i<rdepth;i++){
    rbuffer[i] += d;
    acc += d;
  }
  offset = d;
}
