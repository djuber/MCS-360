/** @file deleteItem.cc
    @brief option 10 from main menu
    @author Daniel Uber
*/
#include "inventory.h"
#include "project1.h"
#include "find.h"
#include <cstring>

/** @fn deleteItem() handles option 10 from displayMenu.

    Ask user for unique item code, and if found, confirm item deletion.
    Validated with valgrind for memory leaks.
*/
void deleteItem(){
  std::string s;
  Item *tmp;
  std::vector<Item*>::iterator index;
  bool found=false;
  while(!found){
    std::cout<<"Enter Product ID Code : ";
    std::cin>>s;
    index = find(s,inventory,found);
    if(!found){
      std::cout<<"Code not found.\n"
	       <<"Enter q to return to main menu, c to continue: ";
      std::cin>>s;
      if(!strcmp(s.c_str(),"q"))
	return;
    }
  } //while !found
  tmp = *index;
  while(true){
    std::cout<<"ready to delete " << (*tmp).Name()
	     <<". Press c to confirm, q to return to menu : ";
    std::cin>>s;
    if(!strcmp(s.c_str(),"c")){
      inventory.erase(index);
      delete tmp;
      return;
    } else if (!(strcmp(s.c_str(), "q")))
      return;
  }
}
