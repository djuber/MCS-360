/** @file project1.h
    @author Daniel Uber
    @brief function declarations for project1.cc
    and definition of ltstr struct used in map sorting
*/
#ifndef _PROJECT_1_
#define _PROJECT_1_

#include <string>
#include "supplier.h"
#include "dollar.h"
#include "item.h"
#include <vector>

// called by main upon program startup
void runProgram();




/** ltstr is a struct with a string comparison function.

    It is used in sorting keys in reverseLookup.
    Map needs a reliable order.
    Also used in string sort methods for option 6
    (sort file by key) where key is a string field.
*/
struct ltstr{
  /** string comparison for ordering of keys */
  bool operator() (std::string s1, std::string s2){
    return (s1.compare(s2)<0);
 }
};


/** ltint is a struct with an int comparison function.

    It is used in sorting integer fields.
*/
struct ltint{
  /** integer comparison for sorting */
  bool operator() (int i1, int i2){
    return (i1 < i2);
  }
};


/** ltDollar is a struct with a Dollar comparison function.

    It is used in sorting Dollar values.
*/
struct ltDollar{
  /** Dollar value comparison

      First check if whole dollars are different,
      if not check if cents fields are different.
   */
  bool operator() (Dollar d1, Dollar d2){
    return((d1.whole < d2.whole) ||
	   ((d1.whole == d2.whole) &&
	    (d1.cents < d2.cents)));
  }
};

/** ltDouble is a struct with a double comparison function.

    It is used in ordering double values.
*/
struct ltDouble{
  /** compare d1 and d2 */
  bool operator() (double d1, double d2){
    return (d1 < d2);
  }
};

// bool to shorten code, since processResponse will return false to quit
bool displayMenu();
bool processResponse();
// menu item handlers
void handleItemSale();
void dailyReport();
void weeklyCheck();
void monthlyUpdate();
void loadInventory();
void sortFile();
void saveInventory();
void addItem();

void editItem();
void deleteItem();
#endif
