/** @file weeklyCheck.cc
    @author Daniel Uber
    @brief option 3 of the main menu
*/

#include "project1.h"
#include "inventory.h"
#include <iomanip>
/** handles option 3 of displayMenu()

    check stock levels and report items below target level.
*/
void weeklyCheck(){
  std::vector<Item*>::iterator index;
  std::string s;

  std::cout<<std::setw(12)<<"Item UIC"
	   <<std::setw(30)<<"Item Name"
	   <<std::setw(12)<<"Desired Qty"
	   <<std::setw(12)<<"In Stock Qty"
	   <<std::endl;
  if(!inventory.empty())
    for(index = inventory.begin();
	index != inventory.end();
	index++)
      if( (**index).inStock() < (**index).desired())
	std::cout<< std::setw(12)<<(**index).Code()
		 << std::setw(30)<<(**index).Name()
		 << std::setw(12)<<(**index).desired()
		 << std::setw(12)<<(**index).inStock()
		 <<'\n';

  std::cout<< "\n\tType c to continue\n";
  std::cin>>s;
  return;
}














