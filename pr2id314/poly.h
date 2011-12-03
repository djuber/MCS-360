/*-*-c++-*-*/
/** @file poly.h
    @author Daniel Uber
    @brief Declaration of the polynomial class
*/
#ifndef _POLY_H_
#define _POLY_H_

#include <iostream>

/** @class Polynomial
    @brief represents the polynomial as a linked list of terms
*/
class Polynomial{
private:

  /** @class term
      a term in a polynomial expression. Each term has a coefficient and
      a degree. Optionally, other terms will follow via next.
  */
  struct term {

    /** coef, the coefficient of the term */
    double coef;

    /** deg, the degree of the variable in the term */
    unsigned deg;

    /** next a pointer to the remaining terms (if any) */
    term *next;

    /** empty constructor , returns 0 */
    term();

    /** known quantity constructor, returns coef*x^deg */
    term(double coef, unsigned deg);

    /** destructor, sets next to null, unnecessarily */
    ~term();
 };

  /** our list starts here **/
  term * polynomial;

  /** reduce self by combining like terms*/
  void reduce();

  /** exchange two polynomials */
  void swap(Polynomial& other);

 public:
  /** default constructor, gives the zero polynomial */
  Polynomial();

  /** default destructor */
  ~Polynomial();

  /** copy constructor */
  Polynomial(const Polynomial& rhs);
  /** allow promotions */
  Polynomial(const double rhs);

  /** allow construction of monomials */
  Polynomial(const double coef, const unsigned deg);

  /** assignment operator */
  Polynomial& operator=(const Polynomial& rhs);

  /** add a term to the list **/
  void insert(term *t); // implemented
  void insert(double coef, unsigned deg);

  /** extraction operator to read polynomials */
  friend std::istream& operator>>
  (std::istream& is, Polynomial &p);


  /** insertion operator to print polynomials */
  friend std::ostream& operator<<
  (std::ostream& os, const Polynomial& p);

  /** addition operator */
  const Polynomial operator+ (const Polynomial& rhs) const;

  /** subtraction operator */
  Polynomial operator- (const Polynomial& rhs) const;
  /** subtraction/assignment operator */
  Polynomial& operator-=(const Polynomial & rhs);

  /** multiplication operator */
  Polynomial operator* (const Polynomial& rhs) const;
  /** multiplication/assignment operator */
  Polynomial& operator*=(const Polynomial& rhs);

  /** unary negation */
  Polynomial operator- () const;

  /** polynomial evaluation at a point a */
  double operator() (double a) const;

  /** addition/assignment */
  Polynomial& operator+=(const Polynomial& rhs);

  /** make all coefficients positive */
  Polynomial abs() const;

  /** general antiderivative with no arbitrary constant.
      Really, the arbitrary constant is zero here.
      by ignoring the constant
      we lose any meaningful result from antiderivative(0)
      which would have been a constant, but chooses 0
      hence applying twice to 0, which would have
      been an arbitrary constant times x + another
      arbitrary constant, gives 0 for both constants,
      and looks like 0 again
  */
  Polynomial antiderivative () const;

  /** derivative as a polynomial */
  Polynomial derivative () const;

};

// more natural notations

Polynomial abs(const Polynomial& p);

Polynomial derivative(const Polynomial& p);

Polynomial antiderivative(const Polynomial & p);

#endif
