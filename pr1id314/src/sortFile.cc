/** @file sortFile.cc
    @author Daniel Uber
    @brief sort inventory using insertion sort.
*/
#include "inventory.h"
#include "project1.h"
#include <iostream>
#include "isort.h"

/** @fn sortFile() handle option 6 from displayMenu()

    ask user for sort key (using a menu).
    call isort() on inventory using appropriate accessor and comparator.

*/
void sortFile(){
  int response;
  bool selected = false;
  while(!selected){
    std::cout<<"Please select a field to sort by: \n"
	     <<"0. Cancel Sort, return to main menu\n"
	     <<"1. Product Name\n"
	     <<"2. UIC/Product Code\n"
	     <<"3. Quantity in Stock\n"
	     <<"4. Cost of Item\n"
	     <<"5. Price of Item\n"
	     <<"6. Supplier Name\n"
	     <<"7. Supplier Code\n"
	     <<"8. Item Shelf Life\n"
	     <<"9. Average Monthly Volume\n"
	     <<"10. Current Sales total\n";
    std::cout<<"Enter option: ";
    std::cin>>response;
    selected=true; // flip off in default;
    switch(response){
    case 0:
      return;
      break;
    case 1:
      isort<std::vector<Item*>, Item*, nameGetter, std::string, ltstr>
	(inventory);
      break;
    case 2:
      isort<std::vector<Item*>, Item*, codeGetter, std::string, ltstr>
	(inventory);
      break;
    case 3:
      isort<std::vector<Item*>, Item*, stockGetter, int, ltint>
	(inventory);
      break;
    case 4:
      isort<std::vector<Item*>, Item*, costGetter, Dollar, ltDollar>
	(inventory);
      break;
    case 5:
      isort<std::vector<Item*>, Item*, priceGetter, Dollar, ltDollar>
	(inventory);
      break;
    case 6:
      isort<std::vector<Item*>, Item*, supplierNameGetter, std::string, ltstr>
	(inventory);
      break;
    case 7:
      isort<std::vector<Item*>, Item*, supplierCodeGetter, int, ltint>
	(inventory);
      break;
    case 8:
      isort<std::vector<Item*>, Item*, shelfLifeGetter, int, ltint>
	(inventory);
      break;
    case 9:
      isort<std::vector<Item*>, Item*, volumeGetter, double, ltDouble>
	(inventory);
      break;
    case 10:
      isort<std::vector<Item*>, Item*, salesGetter, Dollar, ltDollar>
	(inventory);
      break;
   default:
      selected=false;
      std::cout<<"\nI didn't understand that. Please select "
	       <<"a valid option.\n";
      break;
    } // switch(response)
  }//while not selected
  return;
}
