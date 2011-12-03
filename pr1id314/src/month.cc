/** @file month.cc
    @author Daniel Uber
    @brief Functions for reading and writing months of the year
*/
#include "month.h"
#include <string>
#include <cstring>

/** string value for month
    @return a string in English
*/
std::string months[]={
  "*", //invalid month string
  "January",
  "February",
  "March",
  "April",
  "May",
  "June",
  "July",
  "August",
  "September",
  "October",
  "November",
  "December"};

const std::string printMonth(Month m){
    return months[m];
}

/** read a strictly formatted month string */
Month readMonth(std::string s){
  // list is short, just use brute force
  for(int i = 1; i < 13; i++)
    if(!(strcmp(s.c_str(), months[i].c_str())))
      return Month(i);
  return INVALID;
}

/** read a poorly formatted month string */
Month readMonthSloppily(std::string s){
  Month ret;
  switch(s[0]){
  case 'J':
  case 'j':
    if(s[1]=='a' || s[1]=='A')
      ret= JAN;
    else
      if(s[2]=='l' || s[2]=='L')
	ret= JUL;
      else ret= JUN;
    break;
  case 'F':
  case 'f':
    ret= FEB;
    break;
  case 'D':
  case 'd':
    ret= DEC;
    break;
  case 'N':
  case 'n':
    ret= NOV;
    break;
  case 'M':
  case 'm':
    if(s[2]=='y' || s[2]=='Y')
      ret= MAY;
    else
      ret= MAR;
    break;
  case 'A':
  case 'a':
    if(s[1]=='p' || s[1]=='P')
      ret=APR;
    else
      ret= AUG;
    break;
  case 'S':
  case 's':
    ret= SEP;
    break;
  case 'O':
  case 'o':
    ret= OCT;
    break;
  default:
    ret= INVALID;
  }
  return ret;
}
