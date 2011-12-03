/** @file handleItemSale.cc
    @author Daniel Uber

    @brief option 1 from the main menu.
*/
#include <iostream>
#include <string>
#include <vector>
#include "project1.h"
#include "supplier.h"
#include "dollar.h"
#include "inventory.h"
#include <cstring>
#include "find.h"
///////////////////////////////////////////////////////////////////////////////
/** @fn handleItemSale
    handle option 1 from displayMenu().
    updates total sales for item and checks
    validity of sale quantity
*/
void handleItemSale(){
  std::string uic;
  bool found = false;
  bool valid = false;
  int qty;
  std::vector<Item*>::iterator index;

  while(!found){
    std::cout<<"Enter Product Code, or q to return to main: ";
    std::cin>>uic;
    if(!(strcmp(uic.c_str(), "q")))
      return;
    index=find(uic,inventory, found);
  }

  while(!valid){
    std::cout<<"Enter Quantity Sold: ";
    std::cin>>qty;
    if (std::cin.fail()){
      std::cout<<"Bad Input. I'm looking for a number\n";
      qty=-1;
      std::cin.clear();
      std::cin.ignore(100,'\n');
      valid=false;
      continue;
    }

    if((qty>=0) && (qty <= (**index).inStock()))
      valid=true;
    else
      std::cout<<"There's a problem with that number."
	       <<"\nToo big? Too small?\n";
  }

  // now we have a valid quantity to deduct from
  // a valid item in stock
  // remove qty from the shelf
  (**index).inStock((**index).inStock() - qty);
  // ring the cash register!
  // consider moving this addition/multiplication code elsewhere
  // except this is the only place I multiply or add Dollars
  Dollar sales;
  Dollar price;
  sales = (**index).sales();
  price = (**index).Price();
  price.whole*=qty;
  price.cents*=qty;
  if(price.cents >= 100)
    price.whole+=price.cents/100;
  price.cents%=100;
  sales.whole+=price.whole;
  sales.cents+=price.cents;
  (**index).sales(sales);
  return;
}
