/** @file addItem.cc
    @brief option 8 from main menu
    @author Daniel Uber
*/
#include "project1.h"
#include "inventory.h"
#include <cstring>
#include "find.h"
#include "editItem.h"
/** @fn addItem
    handle option 8 from displayMenu()

    Use edit item after creation to allow out of order completion.
 */
void addItem(){
  Item* item = new Item();
  std::string s;
  char buf[5000];

  //setup item fields
  /* item name */
  std::cout<<"Enter Item Name: ";
  std::cin.getline(buf,4999);
  size_t i = 0;
  while(buf[i]==' ') ++i; //skip whitespace
 (*item).Name(std::string(buf + i)); //names don't have to be unique
  bool found=true;
  while(found){
    std::cout<<"Enter Unique Identification Code: ";
    std::cin>>s;
    find(s,inventory,found);
    if(found){
      std::cout<<"Code already in use.\n"
	       <<"Enter q to return to main menu, c to continue: ";
      std::cin>>s;
      if(!strcmp(s.c_str(),"q")){
	delete item;
	return;
      } // if "q"
    } // if found
  } //while(found)
  (*item).Code(s);
  inventory.push_back(item);
  // since push really does go to the back, don't find() it
  std::vector<Item*>::iterator index = inventory.end()-1;
  // now use edit item to flush out the details
  editItem(index);
}
