/** @file dailyReport.cc
    @brief option 2 from main menu

    definition of dailyReport function.
*/
#include "project1.h"
#include <iomanip>
#include "inventory.h"

/** @fn dailyReport
    handle option 2 from displayMenu()
    prints daily report for each item
*/
void dailyReport(){
  std::vector<Item*>::iterator index;
  std::string s;

  std::cout<<std::setw(12)<<"Item UIC"
	   <<std::setw(30)<<"Item Name"
	   <<std::setw(12)<<"Sales Total"
	   <<std::endl;
  if(!inventory.empty())
    for(index = inventory.begin();
	index != inventory.end();
	index++)
      std::cout<< std::setw(12)<<(**index).Code()
	       << std::setw(30)<<(**index).Name()
	       << std::setw(12)<<(**index).sales().print()
	       <<'\n';

  std::cout<< "\n\tType c to continue\n";
  std::cin>>s;
  return;
}
