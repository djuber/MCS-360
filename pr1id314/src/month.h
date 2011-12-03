/** @file month.h
    @author Daniel Uber
    @brief Month type and a print formatter for it.
*/

#ifndef _MONTH_H_
#define _MONTH_H_
#include <string>

/** months of the year */
enum Month{INVALID,JAN,FEB,MAR,APR,MAY,JUN,JUL,AUG,SEP,OCT,NOV,DEC};

/**return a string to show the month */
const std::string printMonth(Month m);

/** read a well formatted month string
    @return Month, defaults to INVALID
    @param s : a perfect match for the output
*/
Month readMonth(std::string s);

/** read a poorly formatted month string
    @return Month, defaults to INVALID
    @param s : a sloppy match for the output
*/
Month readMonthSloppily(std::string s);

#endif
