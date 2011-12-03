/** @file main.cc
    @author Daniel Uber
    @brief Start menu system.
*/
#include "menu.h"

/**
    @fn main
    simple program logic,
    creates a self starting menu object
*/
int main(){
  PolynomialMenu m;
  return 0;
 }

/**
   @mainpage
   Polynomial Manipulation Program.
   MCS 360 Fall 2011 Project 2

   @section Overview
   This is a menu driven program which allows a user to input polynomials of
   arbitrary length and degree. Operations including multiplication and
   addition of polynomials is available for any previously defined polynomials,
   and all results are saved for future use.

   @section Use
   To begin, add polynomials to work with. The input routine first asks for
   the number of terms in the polynomial, and then for each term requests
   a degree and a coefficient. The resulting polynomial is the sum of the
   given terms. Polynomials are always stored and displayed in ascending
   degree, and reduced by combining like terms.

   Once polynomials have been added to the system, they may
   be recalled by numbers (in order of creation). Unneeded terms may be
   deleted when the number of polynomials in memory makes using the system
   unpleasant.

   Polynomials may be added, subtracted, or multiplied. A special case for
   multiplying by a scalar is allowed, which is simply a constant polynomial
   under the hood.

   @section Cavaets
   It should be noted that multiplying two very large polynomials (number of
   terms) is a time consuming process O(n^2), while addition and evaluation
   at a point are O(n).

   Scalar multiplication cowardly refuses to multiply by zero. The user is
   welcome to solve this himself.

   Coefficients are represented using machine doubles. Repeated
   multiplication or addition will result in <i>inf</i> as a value.
   Precision is inversely proportional to magnitude for doubles. No attempt
   to minimize errors was made.

   @section History
   This was the second programming project for MCS 360 at UIC in Fall 2011.
   Substantial portions of the menu system and the user input routines
   were adapted from the first project. Any future revisions would do well
   to modularize further the menu object, and possibly allow
   reassignment of the istream/ostream for the InputValidator.
*/
