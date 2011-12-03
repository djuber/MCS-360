// quiz7.cc
// MCS 360 Fall 2011
// Daniel Uber

#include "quiz7.h"
#include "delimiter.h"
#include <iostream>
#include <string>

int quiz7(){
  std::string s;
  int retval;
  std::cout<<"Enter Filename to check: ";
  std::cin>>s;
  retval = delimiter(s);
  return retval;
}
