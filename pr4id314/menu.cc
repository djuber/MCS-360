/** @file menu.cc
    @author Daniel Uber
    @brief Menu for Binary Search Tree Demo Program
*/
#include "menu.h"
#include <iostream>
#include <fstream>

/** initialize the tree, start the menu system.
 */
Menu::Menu(){
  root = NULL;
  while(displayMenu() && processResponse()) ;
}

/** remove the tree */
Menu::~Menu(){
  while(root)
    remove(root->data);
}

/** displayMenu
    @brief Show the available options
*/
bool Menu::displayMenu() {
  std::cout<<"\n\t0. Quit\n"
      <<"\t1. Insert File\n"
      <<"\t2. Save to File\n"
      <<"\t3. Insert an Integer\n"
      <<"\t4. Delete an Integer\n"
      <<"\t5. Lookup an Integer\n"
      <<"\t6. Display the tree\n"
      <<"\t7. Generate dot File\n"
      <<"\t8. Summary information\n";
  return true;
}

/** processResponse
    @brief get input from user, if it's an option, call
    the right method
*/
bool Menu::processResponse() {
  int response;
  response = iv.guardedInput("\t\tPlease choose an option: ",
			     "\t\tSelect an option from above: ", -1);
  switch(response){
  case 0:
    return false;
    break;
  case 1:
    insertFile();
    break;
  case 2:
    writeToFile();
    break;
  case 3:
    insertInteger();
    break;
  case 4:
    deleteInteger();
    break;
  case 5:
    lookup();
    break;
  case 6:
    displayTree();
    break;
  case 7:
    generateDotFile();
    break;
  case 8:
    summary(std::cout);
    break;
  }
  return true;
}

/** insertFile
    @brief gobble all integers in file.

    This is fault tolerant, and accepts nonsense.
    For example, makefile (with no numbers in it)
    inserts no numbers. This file inserts the numbers
    -1 through 8 (case statements above and iv arg) but misses
    the 100 and 4999 with no spaces before them below.
*/
void Menu::insertFile() {
  std::cout<<"Enter Name of File to read from: ";
  std::cin.ignore(100,'\n');
  std::cin.getline(buf,4999);
  try {
    std::ifstream infile(buf);
    if(!infile) throw (std::ifstream::failure("Not Opened"));
    int g;
    while(!infile.eof()){
      infile>>g;
      if(!infile.fail())
	insert(g);
      else
	infile.clear(); // recover
      infile.ignore(200,' '); //advance to next token
    }
    infile.close();
  } catch (std::ifstream::failure){ // is this right?
    std::cerr<<"Failed to open "<<std::string(buf)<<'\n';
  }
}

/** insertInteger
    @brief prompt for input, add to tree
*/
void Menu::insertInteger(){
  insert(iv.input("Enter an integer to add: "));
}

/** deleteInteger
    @brief prompt for input, remove from tree
*/
void Menu::deleteInteger(){
  remove(iv.input("Enter an integer to remove: "));
}

/** just print the items in the tree in ascending order */
void Menu::displayTree(){
  display(std::cout);
}

/** generateDotFile
    @brief ask user for a filename, print graphviz
    statements to it.
*/
void Menu::generateDotFile(){
  if(root){
    std::cout<<"Enter Name of File to write to: ";
    std::cin.ignore(100,'\n');
    std::cin.getline(buf,4999);
    try {
      writeDotFile(std::string(buf));
      std::cout<<"Successfully wrote "<<buf<<'\n'
	       <<"You can run make graphics to generate png and svg images.\n";
    } catch (std::ofstream::failure){
      std::cerr<<"Error writing "<<buf<<'\n';
    }
  }
}

/** writeToFile
    @brief generate a sorted list of the items in the tree
    and dump them space separated to the filename given by
    the user.
*/
void Menu::writeToFile(){
  std::cout<<"Enter Name of File to write to: ";
  std::cin.ignore(100,'\n');
  std::cin.getline(buf,4999);
  try {
    std::ofstream outfile(buf);
    if(!outfile) throw std::ofstream::failure("Error");
    display(outfile);
    outfile.close();
  } catch (std::ofstream::failure){
    std::cerr<<"Error writing "<<buf<<'\n';
  }
}

/** lookup
    @brief Confirm presence of an integer

    in a real world application, this dictionary would
    have values associated with the keys, and something
    more useful would happen here.
*/
void Menu::lookup(){
  int n = iv.input("Enter integer to find: ");
  if(find(n))
    std::cout<<n<<" is present in the tree.\n";
  else
    std::cout<<n<<" is not present in the tree.\n";
}
