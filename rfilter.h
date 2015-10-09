#ifndef _RFILTER_H_
#define _RFILTER_H_

class rfilter{
 public:
  rfilter(int depth, int range);
  int inout(int x);
  int output(void);

 private:
  int *rbuffer;
  int wrpos;
  int rdepth;
  int offset;
  int rrange;
  long acc;
  void rshift(int d);
  int inst;
  static int instx;
};

#endif
