/** @file editItem.cc
    @brief option 9 from main menu
    @author Daniel Uber
*/
#include "inventory.h"
#include "project1.h"
#include <cstring>
#include "find.h"
#include "InputValidator.h"
/** editItem handles user input of item details.

    @pre index is either end if called from menu
    or the index of the new item if called from addItem

*/
void editItem(std::vector<Item*>::iterator index){

  bool found = false;
  int response = 0;
  int qty;
  double average;
  Dollar dol;
  Supplier sup;
  char buf[5000];
  std::string s;

  InputValidator<int> intValidator;
  InputValidator<Dollar> dollarValidator;
  InputValidator<double> dblValidator;
  if( index != inventory.end()){
    found = true;
    s = (**index).Code();
  }
  while(!found){
    std::cout<<"Enter Product Code, or q to return to main: ";
    std::cin>>s;
    if(!(strcmp(s.c_str(), "q")))
      return;
    index=find(s,inventory, found);
  }
  while (true){
    std::cout<<"Select Information to Update\n"
	     <<"0. Return to Main Menu\n"
	     <<"1. Item Name : "<<(**index).Name() << '\n'
	     <<"2. Item Code : "<<s<<'\n'
	     <<"3. Item Quantity in Stock : " << (**index).inStock()<<'\n'
	     <<"4. Desired Stock Quantity : " << (**index).desired()<<'\n'
	     <<"5. Item Cost : " << (**index).Cost().print() << '\n'
	     <<"6. Item Price : " << (**index).Price().print() << '\n'
	     <<"7. Item Supplier Name : "<<(**index).supplierName()<<'\n'
	     <<"8. Item Supplier Code : "<<(**index).supplierCode()<<'\n'
	     <<"9. Item Shelf Life : " << (**index).ShelfLife() <<'\n'
	     <<"10. Average Monthly Volume : " << (**index).volume()<<'\n'
	     <<"11. Current Month Sales Totals : " << (**index).sales().print() 
	     << '\n';

    response=intValidator.input("Please select an option : ");

    switch(response){
    case 0:
      return;
      break;
    case 1:
      std::cin.ignore(100,'\n');
      std::cout<<"Enter Item Name: ";
      std::cin.getline(buf,4999);
      (**index).Name(std::string(buf));
      break;
    case 2:
      found = true;
      while(found){
	std::cout<<"Enter Unique Identification Code: ";
	std::cin>>s;
	find(s,inventory,found);
	if(found){
	  std::cout<<"Code already in use.\n"
		   <<"Enter q to return to main menu, c to continue: ";
	  std::cin>>s;
	  if(!strcmp(s.c_str(),"q"))
	    return;
	}
      }
      (**index).Code(s);
      break;
    case 3:
      qty=-1;
      while(qty<0)
	qty=intValidator.guardedInput("Enter quantity in stock : ",
				      "Bad Input. I'm looking for a number\n.",
				      -1);
      (**index).inStock(qty);
      break;
    case 4:
      qty=-1;
      while(qty<0)
	qty=intValidator.guardedInput("Enter desired stock level: ",
				      "Bad Input. I'm looking for a number\n",
				      -1);
      (**index).desired(qty);
      break;
    case 5:
      dol.whole=0;
      dol.cents=-1;
      while(dol.cents > 99 || dol.cents < 0)
	dol=dollarValidator.guardedInput("Enter cost per unit : ",
					 "Bad Input. I'm looking for a DD.CC amount\n",
					 dol);
      (**index).Cost(dol);
      break;
    case 6:
      dol.whole=0;
      dol.cents=-1;
      while(dol.cents > 99 || dol.cents < 0)
	dol=
	  dollarValidator.guardedInput("Enter sales price per unit : ",
				       "Bad Input. I'm looking for a DD.CC amount\n",
				       dol);
      (**index).Price(dol);
      break;
    case 7:
      std::cin.clear();
      std::cin.ignore(100,'\n');
      std::cout << "Enter Supplier Name: ";
      std::cin.getline( buf, 4999);
      s =(std::string(buf));
      sup = (**index).supplier();
      sup.name=(s);
      (**index).supplier(sup);
      break;
    case 8:
      qty=-1;
      while(qty<0)
	qty=intValidator.guardedInput("Enter Supplier Code : ",
				      "Bad Input. I'm looking for a number\n.",
				      -1);
      sup = (**index).supplier();
      sup.code = qty;
      (**index).supplier(sup);
      break;
    case 9:
      qty=-1;
      while(qty<0)
	qty=
	  intValidator.guardedInput("Enter shelf life (in days) : ",
				    "Bad Input. I'm looking for a number\n.",
				    -1);
      (**index).ShelfLife(qty);
      break;
    case 10:
      average=-1.0;
      while(average<0)
	average=
	  dblValidator.guardedInput("Enter average monthly volume: ",
				    "Bad Input. I'm looking for a number\n",
				    -1.0);
      (**index).volume(average);
      break;
    case 11:
      dol.whole=0;
      dol.cents=-1;
      while(dol.cents > 99 || dol.cents < 0)
	dol=
	  dollarValidator.guardedInput("Enter item sales this month : ",
				       "Bad Input. I'm looking for a DD.CC amount\n",
				       dol);
      (**index).sales(dol);
      break;
    default:
      std::cout << "Unrecognized Response.\n";
      break;
    }//switch
  }//while loop
  return;
}


/** @fn editItem() handles option 9 from displayMenu()

    ask user for product code.
    present menu of fields to update.
    act appropriately until user is done.
*/
void editItem(){
  std::vector<Item*>::iterator index = inventory.end();
  editItem(index);
  return;
}
