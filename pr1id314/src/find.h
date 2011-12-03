/** @file find.h
    @author Daniel Uber

    @brief declaration of find()
*/
#ifndef _FIND_H_
#define _FIND_H_
#include "item.h"
#include <vector>
#include <string>
#include <cstring>

std::vector<Item*>::iterator find
(std::string, std::vector<Item*>&,bool&);

#endif
