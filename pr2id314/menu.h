/** @file menu.h
    @author Daniel Uber
    @brief definition of the polynomial menu system
*/
#ifndef _MENU_H_
#define _MENU_H_

#include "poly.h"
#include "InputValidator.h"

#include <iostream>
#include <vector>
#include <utility>

/** @class PolynomialMenu

    @brief The main program logic, contains a vector of
    Polynomials, means to generate them, means to add and multiply
    existing polynomials, handles user input/output, and displays
    the menu and the polynomials in the vector.

    This is less a proper object than a grouping of related functions,
    the class mechanism was used to share what otherwise would have
    been global variables (vector of polynomials),
    or commonly reused items in many functions (input validator objects).
*/

class PolynomialMenu {
public:
  /**
    @fn PolynomialMenu
    Constructor calls runProgram
  */
  PolynomialMenu();
 private:
  std::vector<Polynomial> vp;
  InputValidator<unsigned> uv;
  InputValidator<double> dv;
  InputValidator<int> iv;
  /**
     @fn select
     User selection of one polynomial in the vector
     @return a polynomial from the vector,
     or the 0 polynomial
   */
  Polynomial select();
  /**
     @fn select2
     User selection of two polynomials in the vector
     @return pair of polynomials or a pair of zeros if empty
   */
  std::pair<Polynomial,Polynomial> select2();
  /**
     @fn evaluatePolynomial
     Prompt user for a number and a polynomial to evaluate at
     that number, display result.
   */
  void evaluatePolynomial();
  /**
     @fn display
     Show the contents of the vector
  */
  void display();
  /**
     @fn multiplyPolynomials
     uses select to obtain two polynomials to multiply, stores
     result in vector
  */
  void multiplyPolynomials();
  /**
     @fn addPolynomials
     uses select to obtain two polynomials to add, stores
     result in vector
  */
  void addPolynomials();
  /**
     @fn subtractPolynomials
     uses select to obtain two polynomials to subtract,
     stores first - second  in vector
  */
  void subtractPolynomials();
  /**
     @fn scalePolynomial
     select a polynomial, ask for a scale factor (double)
     and push result of multiplication to the vector.
  */
  void scalePolynomial();
  /**
     @fn derivativePolynomial
     select a polynomial and push the derivative to the vector
   */
  void derivativePolynomial();
  /**
     @fn antiderivativePolynomial
     select a polynomial, push the indefinite integral to the vector
  */
  void antiderivativePolynomial();
  /**
     @fn inputPolynomial
     User input routine, prompt for number of terms,
     and for each term, prompt for degree and coefficient.
     @return polynomial as sum of the entered terms
  */
  Polynomial inputPolynomial();
  /**
     @fn deletePolynomial
     Removes an item from the vector, or does nothing
     if the vector is empty.
   */
  void deletePolynomial();
  /**
     @fn displayMenu
     Prints the menu
     @return true.
   */
  bool displayMenu();
  /**
     @fn processResponse
     reads an integer response, and calls appropriate method.
     will reprompt if an invalid response was entered.
     @return true, or false if quit was selected.
   */
  bool processResponse();
  /**
     @fn runProgram
     alternately displays the menu, then handles user input
     when processResponse returns false, exits.
  */
  void runProgram();
};

#endif
