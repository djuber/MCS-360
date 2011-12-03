/** @file dollar.cc
    @author Daniel Uber

    @brief Dollar class insertion and extraction operators.
    see dollar.h for Dollar structure details.
*/
#include "dollar.h"

std::istream& operator>> (std::istream& is, Dollar& dollar)
{
  int whole, cents;
  is>>whole;
  is.ignore();
  is>>cents;
  dollar.whole=whole;
  dollar.cents=cents;
  return is;
}

std::ostream& operator<< (std::ostream& os, Dollar& dollar)
{
  os<<dollar.print();
  return os;
}

std::string Dollar::print(){
    std::stringstream s;
    // insert significant 0 where needed
    std::string cent;
    if(cents<10)
      cent="0";
    else
      cent="";
    s<<whole<<'.'<<cent<<cents;
    return s.str();
  }

bool Dollar::operator==(const Dollar & rhs){
  if((whole==rhs.whole) && (cents==rhs.cents))
    return true;
  else
    return false;
}
