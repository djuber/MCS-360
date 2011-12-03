// Ratio.h
// Daniel Uber MCS 360 Quiz 5
// class Ratio interface description

#ifndef RATIO_H
#define RATIO_H
#include <iostream>

class Ratio{
  friend std::ostream& operator<<(std::ostream& out, const Ratio& rhs);
  friend std::istream& operator>>(std::istream& in, Ratio& rhs);
  int * pnum;
  int * pden;
public:
  Ratio(): pnum(new int(0)), pden(new int(1)) {}
  Ratio(int num, int den=1) : pnum(new int(num)), pden(new int(den)) {}
  Ratio(const Ratio& rhs);
  ~Ratio() { delete pnum; delete pden;}
  Ratio& operator=(const Ratio& rhs);
  int Num() const {return *pnum;}
  int Den() const {return *pden;}
  void Num(int num) {*pnum = num;}
  void Den(int den) {*pden = den;}
  void simplify();
};

#endif
