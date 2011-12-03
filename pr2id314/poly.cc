/** @file poly.cc
    @author Daniel Uber
    @brief Implementation for the polynomial class
*/

#include "poly.h"
#include <cstring>


/** create an empty term */
Polynomial::term::term() {
  coef = 0;
  deg = 0;
  next = NULL;
}

/** create a term of degree deg and coefficient coef  */
Polynomial::term::term(double coef, unsigned deg){
  this->coef = coef;
  this->deg = deg;
  this->next = NULL;
  //  this->prev = NULL;
}

/** destructor for terms */
Polynomial::term::~term(){
  // really needs to happen ahead of time...
  this->next=NULL;
  //  this->prev=NULL;
}

/** default constructor, returns a zero polynomial */
Polynomial::Polynomial(){
  // get the zero term
  polynomial = new term(0.0, 0);
}

Polynomial::Polynomial(const double rhs){
  polynomial = new term(rhs,0);
}

Polynomial::Polynomial(const double coef, const unsigned deg){
  polynomial = new term(coef, deg);
}

/** delete each term before expiring */
Polynomial::~Polynomial(){
  term * t;
  while(polynomial){
    t = polynomial;
    polynomial = t->next;
    delete t;
  }
}

/** insert : add to list & reduce
    insert is in degree order
    polynomial is maintained in sorted order
    reduce only combines like terms.
*/
void Polynomial::insert(term * t){
  term * u = polynomial;
  term * prev = NULL;
  while(u->next && ( t->deg > u->deg)){
    prev = u;
    u = u->next;
  }
  if (u == polynomial && !(t->deg >= u->deg)){
    //still at head of list, and t is not bigger
    polynomial = t;
    t->next = u;
  }  else if (t->deg > u->deg){
    // got to end of list
    u->next = t;
  }
  else {
    // in the middle
    t->next = u;;
    if(prev)
      prev->next = t;
    else polynomial = t;
  }
  reduce();
  return;
}

/** insert : doesn't require user to call constructor for term */
void Polynomial::insert(double coef=0, unsigned deg=0){
  term * t = new term(coef, deg);
  insert(t);
  return;
}

Polynomial& Polynomial::operator+=(Polynomial const &other)
{
  Polynomial tmp(*this);
  term * t = other.polynomial;
  while(t){
    tmp.insert(t->coef,t->deg);
    t=t->next;
  }
  swap(tmp);
  return *this;
}


const Polynomial Polynomial::operator+
(const Polynomial& rhs) const
{
  Polynomial tmp(*this);
  tmp += rhs;
  return tmp;
}

/** evaluate at point a */
double Polynomial::operator()
  (double a) const
{
  Polynomial p;
  term *t, *u;
  unsigned degree;
  double result = 0;
  // first reverse order the list
  // since the polynomial is sorted,
  // just peel off to the front each time.
  t = polynomial;
  while (t){
    u =  p.polynomial;
    p.polynomial = new term(*t);
    t = t->next;
    p.polynomial->next = u;
  }
  // seed with the highest order term
  t = p.polynomial;
  degree = t->deg;
  // now evaluate the polynomial at a
  while(t){
    // multiply result by a
    while(degree > t->deg){
      result *= a;
      degree--;
    }
    // add next coefficient
    result += t->coef;
    //remember depth (there might be gaps)
    degree = t->deg;
    // advance
    t = t->next;
  }
  return result;
}

Polynomial Polynomial::operator*
(const Polynomial & rhs) const {
  // for each term in rhs
  // multiply terms by coef and raise power by deg
  Polynomial p;
  term * u;
  term * t = rhs.polynomial;
  while (t) {
    u = polynomial;
    while(u){
      p.insert(u->coef * t->coef, u->deg + t->deg);
      u = u->next;
    }
    t = t->next;
  }
  return p;
}

Polynomial& Polynomial::operator*=(const Polynomial& rhs) {
  *this = *this * rhs;
  return *this;
}

/** unary negation operator
    just multiply by a scalar -1
*/
Polynomial Polynomial::operator-() const
{
  return this->operator*(-1.0);
}

/** subtraction operator
    add -rhs
*/
Polynomial Polynomial::operator-(const Polynomial& rhs) const {
  return *this + -rhs;
}

Polynomial& Polynomial::operator-=(const Polynomial & rhs){
  *this += (-rhs);
  return *this;
}

Polynomial Polynomial::derivative() const {
  Polynomial p;
  term *t = polynomial;
  while(t){
    if(t->deg)
      p.insert((t->coef * t->deg), t->deg - 1);
    t = t->next;
  }
  return p;
}
/** @fn derivative(const Polynomial &p)
    return polynomial derivative
*/
Polynomial derivative(const Polynomial & p){
  return p.derivative();
}

Polynomial Polynomial::abs() const{
  Polynomial tmp(*this);
  term *t = tmp.polynomial;
  while(t){
    if (t->coef <  0)
      t->coef *= -1;
    t = t->next;
  }
  return tmp;
}
/** @fn abs(const Polynomial &p)
    @return absolute value of polynomial
*/
Polynomial abs(const Polynomial& p){
  return p.abs();
}

Polynomial Polynomial::antiderivative() const {
  Polynomial p;
  term *t = polynomial;
  while(t){
    if(t->deg == 0)
      p.insert(t->coef, 1);
    else
      p.insert( t->coef /(1.0+ t->deg), t->deg+1);
    t=t->next;
  }
  return p;
}
/** @fn antiderivative(const Polynomial &p)
    @return indefinite integral of p with constant 0
*/
Polynomial antiderivative(const Polynomial & p) {
  return p.antiderivative();
}
/** immensely useful function for any type */
void Polynomial::swap(Polynomial &other)
{
  char buffer[sizeof(Polynomial)];
  memcpy(buffer, &other, sizeof(Polynomial));
  memcpy(&other, this,   sizeof(Polynomial));
  memcpy(this,   buffer, sizeof(Polynomial));
}


/** assignment operator */
Polynomial& Polynomial::operator=(const Polynomial & rhs){
  if(this != &rhs){
    Polynomial tmp(rhs);
    swap(tmp);
  }
 return *this;
}

/** copy constructor */
Polynomial::Polynomial(const Polynomial& rhs){
  term * t;
  // initialize
  polynomial = new term();
  // copy
  t = rhs.polynomial;
  while(t){
    insert(t->coef, t->deg);
    t = t->next;
  }
}


/** @fn Polynomial::reduce
    @brief combine like terms and eliminate redundancies
    @post each degree in polynomial has a single term
*/
void Polynomial::reduce(){
  term * t = polynomial;
  term * tmp;
  if(t != NULL)
    while((t != NULL) && (t->next != NULL)){
      //combine like terms
      if(t->deg == t->next->deg){
	tmp = t->next;
	t->coef += tmp->coef;
	t->next = tmp->next;
	// remove redundant terms
	delete tmp;
      }
      // move forward
      if(t)
	t = t->next;
    } // while next is not null
  return;
}

/** operator<<
    insert polynomial into an output stream
    terms will be printed in order of increasing degree
 */
std::ostream& operator<<(std::ostream& os, const Polynomial& p){
  Polynomial::term * t;
  t = p.polynomial;
  bool first = true;
  while(t){
    if(t->coef != 0.0){
      if(!first)
	os<<" + ";

      os<< t->coef;
      if(t->deg){
	os<<"*x";
	if(t->deg > 1)
	  os<<"^"<<t->deg;
      }
      //    os<<" ";
    first = false;
   }
    t = t->next;

  }
  if (first)
    os<<"0";
  return os;
}

/** extraction operator
    get a pair of numbers double, unsigned from an istream
    This might not be the best way to do this,
    and is nowhere used.
*/
std::istream& operator>>(std::istream& is, Polynomial &p){
  double coef;
  unsigned int  degree;
  Polynomial::term *t;
  coef = 0.0;
  while (coef == 0.0){
    is>>coef;
    is>>degree;
    if(!is.fail()){
      t = new Polynomial::term(coef, degree);
      p.insert(t);
    }
  }
  return is;
}
