/* Local Variables: */
/* mode: c++ */
/* End: */

/** @file project3.h
    @author Daniel Uber
    @brief declarations of functions and types for project 3
    necessary includes are also here.
*/

#ifndef _PROJECT_3_H_
#define _PROJECT_3_H_

#include <string>
#include <sstream>
#include <iostream>
#include "stack.h"

/** class Operator
    @brief our binary operations are derived from these
*/
class Operator{
public:
  /** all Operators are callable */
  virtual double operator()
  (double a, double b)=0;
};

/** class InvalidExpression
    @brief an exception type
    some of our functions throw this
*/
class InvalidExpression{};

// utilities.cc
/** toDouble tries to convert a string to a number */
double toDouble(std::string t) throw (InvalidExpression);

/** isWhitespace looks to see if there is a non-blank character */
bool isWhitespace(char c);

/** isWhitespace looks for any non-blank character */
bool isWhitespace(std::string s);

/** isBracket returns true for '(' or ')' */
bool isBracket(std::string s);

/** isOperator returns true for valid arithmetic symbols */
bool isOperator(std::string s);

/** getOperator gives an object related to operator string */
Operator& getOperator(std::string s) throw (InvalidExpression);

/** precedence is less than for operator strings */
bool precedence(std::string s, std::string t);

/** precedence2 is less than or equal to */
bool precedence2(std::string s, std::string t);

// in infixFormat.cc
/** infixFormat puts spaces between arguments, operators,
    and brackets
*/
std::string infixFormat(std::string &s);

// in postfixFormat.cc
/** infix2postfix calls postfixFormat */
std::string infix2postfix(std::string infix);

/** postfixFormat takes an infix expression and
    returns an postfix expression */
std::string postfixFormat(std::string s);

// in postfixEval.cc
/** eval_postfix calls postfixEval */
double eval_postfix(std::string postfix);

/** postfixEval evaluates a postfix string */
double postfixEval(std::string s);

// in main.cc
int main();

#endif
