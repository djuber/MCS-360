/** @file dollar.h
    @author Daniel Uber
    @brief The Dollar struct and its members.
*/

#ifndef _DOLLAR_H_
#define _DOLLAR_H_
#include <iostream>
#include <string>
#include <sstream>

/** Dollar is a convenient way to store
    a simple currency amount.

    In places where there is not a 1/100 relationship between the
    currency units, a change is required in the way we calculate
    fractions.
*/

struct Dollar{
  /** whole is the integer dollar amount */
  int whole;
  /** cents is the fractional dollar amount */
  int cents;
  /** create a double from the dollar amount.
      @return whole + .01*cents, a good approximation
  */
  double toDouble(){return 1.0*whole + .01*cents;}

  /** update using a double
      @param amount is a double representation of the amount
  */
  void fromDouble(double amount){
    std::stringstream s;
    s<<amount;
    int a,b;
    s>>a;
    s.ignore();
    s>>b;
    whole = a;
    cents = b;
  }


  /** create dollar from dollars and cents
      @param whole is the whole dollar amount
      @param cents is the cents amount
  */
  Dollar(int whole, int cents){this->whole=whole;this->cents=cents;}

 /** create dollar from float
      @param amount is a double representation of the amount
      @note you may move a penny if whole is large due to precision
  */
  Dollar(double amount){whole = int(amount);
    cents=int( 100 * (amount - int(amount)));
    cents+=((1000*amount)>=5)?1:0;}

  /** default constructor
      new Dollar is $0.00
  */
  Dollar(){whole=cents=0;}
  /** operator==
      @brief equality comparison. Used in inputValidator<Dollar>
      @see InputValidator.h

      Two dollar amounts are equal when the whole and cents are both
      equal. Otherwise they are unequal.
  */
  bool operator==(const Dollar & rhs);
  /** return a string that looks nice */
  std::string print();
};

/** extract Dollar from istream */
std::istream& operator>> (std::istream& is, Dollar& dollar);
/** insert Dollar to ostream */
std::ostream& operator<< (std::ostream& os, Dollar& dollar);
#endif
