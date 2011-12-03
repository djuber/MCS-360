/** @file supplier-map.cc
    @author Daniel Uber

    @brief Functions to track the supplier data
*/

#include <map>
#include <string>
#include "project1.h"
#include "supplier.h"
#include "supplier-map.h"

/** lookup stores the supplier names by code key */
std::map<int, std::string > lookup;

/** reverseLookup stores the supplier codes by name key */
std::map<std::string, int, ltstr> reverseLookup;

/* Supplier Code related functions*/

/** add a supplier's data to the lookup tables.
    @param s is a Supplier to be added.
*/
void addSupplier(Supplier s){
  std::pair<int, std::string> p1(s.code, s.name);
  std::pair<std::string, int> p2(s.name, s.code);
  lookup.insert(p1);
  reverseLookup.insert(p2);
  return;
}

/** Lookup supplier name from code.
    @param c is a supplier code in the table.
    @return a string name of the supplier matching the code.
*/
std::string SupplierNameFromCode(int c) {
  std::map<int, std::string>::iterator i;
  i = lookup.find(c);
  return (*i).second;
}

/** Reverse lookup of supplier code.
    @param s is a string name of a supplier.
    @return supplier code, an integer
*/
int SupplierCodeFromName(std::string s){
  std::map<std::string, int>::iterator i;
  i = reverseLookup.find(s);
  return (*i).second;
}
