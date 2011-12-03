/** @file inventory.h
    @author Daniel Uber

    @brief included by any file using the inventory vector

    inventory is a global variable in project1.cc
*/

#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include "item.h"
#include <vector>

extern std::vector<Item*> inventory;

#endif
