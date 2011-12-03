/** @file menu.cc
    @author Daniel Uber
    @brief implement the menu logic
*/

#include "menu.h"

using namespace std;

Polynomial PolynomialMenu::select(){
  display();
  unsigned index;
  unsigned limit = vp.size();
  if(limit==0) return 0;
  index = limit;
  while(index >= limit)
    index = uv.guardedInput("Please select a polynomial: ",
			    "Must be a valid index",
			    -1);
  return vp[index];
}

void PolynomialMenu::evaluatePolynomial(){
  double a;
  Polynomial p = select();
  a = dv.input("Enter point to evaluate at: ");
  cout<<"P("<<a<<")= "<<p(a)<<"\n\n";
  return;
}

void PolynomialMenu::display(){
  vector<Polynomial>::iterator i;
  int c;
  for (i = vp.begin(), c=0; i != vp.end(); i++, c++)
    cout<<"P["<<c<<"]: "<<*i<<'\n';
  return;
}

pair<Polynomial,Polynomial> PolynomialMenu::select2(){
  display();
  unsigned index1;
  unsigned index2;
  unsigned limit = vp.size();
  if(limit==0) return pair<Polynomial, Polynomial> (0,0);
  index1 = limit;
  while(index1 >= limit)
    index1 = uv.guardedInput("Please select a polynomial: ",
			     "Must be a valid index",
			     -1);
  index2 = limit;
  while(index2 >= limit)
    index2 = uv.guardedInput("Please select second polynomial: ",
			     "Must be a valid index",
			       -1);
  return pair<Polynomial,Polynomial> (vp[index1], vp[index2]);
}

void PolynomialMenu::multiplyPolynomials(){
  pair<Polynomial,Polynomial> p = select2();
  vp.push_back(p.first * p.second);
  return;
}

void PolynomialMenu::addPolynomials(){
  pair<Polynomial, Polynomial> p = select2();
  vp.push_back(p.first + p.second);
  return;
}

void PolynomialMenu::subtractPolynomials(){
  pair<Polynomial,Polynomial> p = select2();
  vp.push_back(p.first - p.second);
}

void PolynomialMenu::scalePolynomial(){
  vp.push_back(Polynomial(1) * // dummy value to help compiler find *
	       dv.guardedInput("Enter Scale factor: ",
			       "Non-zero values make sense here",
				0.0)
	       * select());
  return;
}

void PolynomialMenu::derivativePolynomial() {
  vp.push_back(derivative(select()));
}

void PolynomialMenu::antiderivativePolynomial() {
  vp.push_back(antiderivative(select()));
}

Polynomial PolynomialMenu::inputPolynomial(){
  Polynomial p;
  Polynomial *a;
  double coef;
  unsigned deg;
  unsigned terms;
  terms = uv.input("Enter number of terms to add: ");
  while(terms){
    deg = uv.guardedInput("Enter degree of term: ",
			  "Degree must be nonnegative: ",
			  -1);
    coef = dv.input("Enter coefficient of term: ");
    a = new Polynomial(coef,deg);
    p += *a;
    delete a;
    terms--;
  }
  return p;
}

void PolynomialMenu::deletePolynomial(){
  display();
  unsigned index;
  unsigned limit = vp.size();
  if(limit == 0) return;
  index = limit;
  while(index >= limit)
    index = uv.guardedInput("Enter polynomial to delete: ",
			    "Must select a valid polynomial number",
			    -1);
  vp.erase(vp.begin() + index);
  return;
}

bool PolynomialMenu::displayMenu(){
  cout<<"\n\t0. Quit\n"
      <<"\t1. Input Polynomial\n"
      <<"\t2. Display polynomials\n"
      <<"\t3. Add Polynomials\n"
      <<"\t4. Multiply Polynomials\n"
      <<"\t5. Evaluate Polynomial at point\n"
      <<"\t6. Delete Polynomial\n"
      <<"\t7. Subtract Polynomials\n"
      <<"\t8. Scale Polynomial\n"
      <<"\t9. Calculate first derivative\n"
      <<"\t10. Calculate antiderivative\n";
  return true;
}

bool PolynomialMenu::processResponse(){
  int response;
  response = iv.guardedInput("\t\tPlease choose an option: ",
			     "\t\tSelect an option from above: ", -1);
  switch(response){
  case 0:
    return false;
    break;
  case 1: // add to vector of polynomials
    vp.push_back(inputPolynomial());
    break;
  case 2: //  show polynomials in vector
    display();
    break;
  case 3:
    addPolynomials();
    break;
  case 4:
    multiplyPolynomials();
    break;
  case 5:
    evaluatePolynomial();
    break;
  case 6:
    deletePolynomial();
    break;
  case 7:
    subtractPolynomials();
    break;
  case 8:
    scalePolynomial();
    break;
  case 9:
    derivativePolynomial();
    break;
  case 10:
    antiderivativePolynomial();
    break;
  default:
    cout<<"\nUnrecognized response\n";
    break;
  }
  return true;
}


void PolynomialMenu::runProgram(){
  while(displayMenu() && processResponse());
  return;
}

PolynomialMenu::PolynomialMenu(){
  runProgram();
}
