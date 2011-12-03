// file : Ratio.cc
// Ratio Class
// MCS 360 Quiz 5
// Daniel Uber
#include <iostream>
#include <cstdio>
#include "gcd.h"
#include "Ratio.h"

using namespace std;


Ratio::Ratio(const Ratio& rhs){
  //x = 2;
  int x = rhs.Num();
  pnum = new int(x);
  pden = new int(rhs.Den());
}

Ratio& Ratio::operator=(const Ratio& rhs){
 if (this != &rhs){
    this->pnum = new int(rhs.Num());
    this->pden = new int(rhs.Den());
  }
 return *this;
}

void Ratio::simplify(){
  //x =2 ;
int g = gcd(*pnum, *pden);
  *pnum /= g;
  *pden /= g;
  if(*pden < 0)
    *pnum *= -1;
  return;
}


ostream& operator<<(ostream& out, const Ratio& rhs){
  out<<rhs.Num() << '/' << rhs.Den();
  return out;
}

/* won't read other than decimal input. i.e. I don't check for
   Hex or Octal here */
istream& operator>>(istream& in, Ratio& rhs){
  int i, j=0;
  bool den=false; // start with numerator
  bool sign = false; //flip in presence of a minus sign
  while( (i = in.get()) ){
    // division symbol is separator
    if(i == '/'){
      den = true; // now work on denominator
      rhs.Num(j); // write stored value to numerator
      j = 0;
    }
    // stop input at a comma or newline, this likely doesn't belong here
    if(i == ',' || i == '\n'){
      if(den && j != 0) // skip poorly formatted expressions 1 /,
	rhs.Den(j);
      else if(!den)
	rhs.Num(j);
      if (sign) // if we had an odd number of signs, multiply numerator by -1
	rhs.Num(-1*rhs.Num());
      return in;
    }
    if(isdigit(i))
      j = j*10 + i - '0';
    if((i == '-') && (j == 0))
      // ignore spurious - symbols inside a number
      sign = !sign;
  }
  return in;
}

