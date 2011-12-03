/** @file loadInventory.cc
    @author Daniel Uber
    @brief option 5 from main menu

    the loadInventory function: read from file to vector


*/
#include "inventory.h"
#include "project1.h"
#include <fstream>

/** @fn loadInventory
    handle option 5 from displayMeny()

    if filename given is an inventory file,
    existing inventory will be replaced with
    contents of the file. If failure, user can quit or
    try another file.
*/
void loadInventory(){
  std::ifstream infile;
  std::string filename;
  Item * item;
  do {
    std::cout<<"Enter Filename : ";
    std::cin>>filename;
    infile.open(filename.c_str());
  } while (!infile);
  if(infile.peek()=='_') //valid file
    while(!inventory.empty()){
      item = inventory[0];
      delete item;
      inventory.erase(inventory.begin());
    } // inventory is empty
  while(!infile.eof() && !infile.fail()){
    item = new Item();
    infile>>(*item);
    if((*item).Code()=="*" || (*item).Code() == ""){
      delete item;
      infile.ignore(400,'\n');
      //      infile.clear();
    }
    else
      inventory.push_back(item);
  }
  infile.close();
  return;
}
