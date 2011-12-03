/** @file supplier-map.h
    @author Daniel Uber
    @brief functions for maintaining the supplier table
*/
#ifndef _SUPPLIER_MAP_H_
#define _SUPPLIER_MAP_H_
#include "supplier.h"
#include <string>

// used in Item, defined in supplier-map.cc
std::string SupplierNameFromCode(int c);
int SupplierCodeFromName(std::string s);
void addSupplier(Supplier s);

#endif
