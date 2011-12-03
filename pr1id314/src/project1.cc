/** @file project1.cc
    @author Daniel Uber
    @brief Main implementation of project1.

    menu option processing and global inventory are here.
*/

#include <vector>
#include <iostream>
#include "project1.h"
#include "item.h"
#include <cstdlib>
#include <ctime>

/* Globals: */

/** inventory is the vector of pointers to items in the store.

    Declared in inventory.h
*/

std::vector<Item*> inventory;


/**
   Handle input after displayMenu()
 */
bool processResponse(){
  //fixme: need to call functions rather than printing selection
  int response;
  std::cin >> response;
  std::cin.ignore();
  switch(response){
  case 0:
    return false;
    break;
  case 1:
    handleItemSale();
    break;
  case 2:
    dailyReport();
    break;
  case 3:
    weeklyCheck();
    break;
  case 4:
    monthlyUpdate();
    break;
  case 5:
    loadInventory();
    break;
  case 6:
    sortFile();
    break;
  case 7:
    saveInventory();
    break;
  case 8:
    addItem();
    break;
  case 9:
    editItem();
    break;
  case 10:
    deleteItem();
    break;
  default:
    std::cout<<"Unrecognized Entry.\n";
    break;
  }

  std::cout<<"\n\n";
  return true;
}

/** Display a menu of options */
bool displayMenu(){
  std::cout<<"0. Exit\n"
	   <<"1. Item Sale\n"
	   <<"2. Daily Report\n"
	   <<"3. Weekly Check\n"
	   <<"4. Monthly Update\n"
	   <<"5. Load Inventory File\n"
	   <<"6. Sort File by Key\n"
	   <<"7. Save Inventory to File\n"
	   <<"8. Add a new Item\n"
	   <<"9. Edit an Item\n"
	   <<"10. Delete an Item\n";
  return true;
}

/** start a menu processing loop.
*/
void runProgram(){
  srandom(time(NULL));
  while( displayMenu() && processResponse())
    ;

  // process response returned false. Clean up.
  // thanks to valgrind for pointing out
  // any trouble I might have had.
  while(!inventory.empty()){
    Item* k = inventory[0];
    delete k;
    inventory.erase(inventory.begin());
  }
  return;
}

