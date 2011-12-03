/** @file utilities.cc
    @author Daniel Uber
    @brief functions and helper classes used in project 3
*/

#include "project3.h"
#include <cmath> // for pow and floor

/** extend modulus to double */
double modulus(double x, double y){
  double t = x/y;
  return x - y * floor(t);

}


/** class ADD
    @brief a binary operator for postfixEval()
*/
class ADD : public Operator
{
  double operator() (double a, double b){
    return a + b;
  }
};

/** class MINUS
    @brief a binary operator for postfixEval()
*/
class MINUS : public Operator
{
  double operator() (double a, double b){
    return b - a;
  }
};

/** class TIMES
    @brief a binary operator for postfixEval()
*/
class TIMES : public Operator
{
  double operator() (double a, double b){
    return a * b;
  }
};

/** class DIVIDE
    @brief this is a binary operator for the postfixEval
*/
class DIVIDE : public Operator
{
  double operator() (double a, double b){
    if(a==0.0) throw InvalidExpression();
    return b/a;
  }
};

/** class EXP
    @brief this is a binary operator for the postfixEval
*/
class EXP : public Operator
{
  double operator() (double a, double b){
    return pow(b,a);
  }
};

/** class MODULUS
    @brief this is a binary operator for the postfixEval
*/
class MODULUS: public Operator
{
  double operator() (double a, double b){
    if(a==0.0) throw InvalidExpression();
    return modulus(b,a);
  }
};

double toDouble(std::string t) throw (InvalidExpression)
{
  if (t=="") throw InvalidExpression();
  std::stringstream input(t);
  double r=0;
  input>>r;
  if(input.fail()) throw InvalidExpression();
  return r;
}

// not sure how you'd put a vtab in, or a form feed, but why not.
// tried to order these in decreasing likelihood
// so OR could short circuit (backspace should be removed before line
// line completes, but there are still dumb terminals out there.
bool isWhitespace(char c){
  return (c==' ' || c=='\t' || c=='\n' || c==0 ||
	  c=='\v' || c=='\f' || c=='\r' || c=='\b');
}

bool isWhitespace(std::string s){
  // if any character is not whitespace,
  // string is not whitespace
 for(size_t i = 0; i < s.size(); i++)
   if( !isWhitespace(s[i])) return false;
 return true;
}

bool isBracket(std::string s){
  return ( s=="(" || s==")" );
}

/** check for known operations */
bool isOperator(std::string s){
  return (s=="+" || s=="*" || s=="-"
	  || s =="/" || s=="^" || s=="%");
}

Operator& getOperator(std::string s) throw (InvalidExpression){
  static EXP exp;
  static TIMES times;
  static DIVIDE divide;
  static ADD add;
  static MINUS minus;
  static MODULUS modulus;
  if(!isOperator(s)) throw InvalidExpression();
  if(s=="^") return exp;
  if(s=="*") return times;
  if(s=="/") return divide;
  if(s=="+") return add;
  if(s=="%") return modulus;
  else return minus;
}

// // less than for operators: s1 < s2
// // rules: exp > mul=div=mod > add=sub
bool precedence(std::string s1, std::string s2){
  bool value = true;
  // closing parens caught by postfixFormat
  // only open parens needed here
  if(s2=="(") return false;
  // nothing higher than exponentiation
  if(s1=="^") value = false;
  // only exponentiation higher than mult/div, div is not commutative
  else if ((s1 == "*" || s1=="/" || s1=="%")
	   && !(s2=="^" || s2=="/" || s2=="%" || s2=="*"))
    value = false;
  // everything higher than addition or subtraction
  else if ((s1== "+" || s1=="-")) value = true;
  else if (s1==s2) value = true;
  return value;
}

