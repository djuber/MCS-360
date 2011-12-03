/** @file monthlyUpdate.cc
    @author Daniel Uber
    @brief option 4 of the main menu
*/
#include "project1.h"
#include "inventory.h"

/** @fn monthlyUpdate() handles option 4 of displayMenu()

    Set new month for all items. Clear monthly sales totals.
*/
void monthlyUpdate(){
  Month current=INVALID;
  std::string s;
  std::vector<Item*>::iterator index;
  int qty=-1;
  Dollar zero;
  zero.whole=0;
  zero.cents=0;
  while(current==INVALID){
    std::cout<<"Enter name of month: ";
    std::cin>>s;
    current = readMonthSloppily(s);
  }

  if(!inventory.empty())
    for(index = inventory.begin();
	index != inventory.end();
	index++){
      (**index).current_month(current);
      std::cout << "Enter quantity on hand for item "
		<< (**index).Code() << " " << (**index).Name()
		<<". Previous was "<<(**index).inStock() << " : ";
      qty=-1;
      while(qty<0){
	  std::cin>>qty;
	  if (std::cin.fail()){
	    std::cout<<"Bad Input. I'm looking for a number\n";
	    qty=-1;
	    std::cin.clear();
	    std::cin.ignore(100,'\n');
	    std::cout<<"Enter quantity in stock: ";
	  }
      } // qty is now valid
      (**index).inStock(qty);
      (**index).sales(zero);
    } //for index in inventory
  return;
}
