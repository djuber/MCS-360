/** @file editItem.h
    @author Daniel Uber
    @brief this avoids a circular dependency between project1.h
    and item.h
*/

#ifndef _EDIT_ITEM_H_
#define _EDIT_ITEM_H_
#include <vector>
#include "item.h"

void editItem(std::vector<Item*>::iterator);

#endif
