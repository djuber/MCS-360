/** @file find.cc
    @author Daniel Uber

    @brief find string in vector of items.
*/
#include "find.h"
//#include "item.h"
//#include <vector>
//#include <string>
//#include <cstring>

/** find
    looks for an existing unique code in use
    in the inventory. If it finds a duplicate, flag
    is set to true, and the offending item's iterator is
    returned. If the string supplied is unique, flag is
    false and an invalid iterator is returned.
    @param uic the search string
    @param v the vector of items to search in
    @param flag a boolean result indicator
    @return iterator in v, default to v.end()
*/
std::vector<Item*>::iterator
find(std::string uic, std::vector<Item*>& v, bool& flag){
  std::vector<Item*>::iterator index;
  for(index = v.begin(); index != v.end(); index++){
    if(!strcmp( (**index).Code().c_str(), uic.c_str())){
      flag=true;
      return index;
    }
  }
  flag = false;
  return v.end();
}
