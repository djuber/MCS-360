// -*- c++ -*-
/** @file menu.h
    @author Daniel Uber
    @brief Menu for Binary Search Tree Demo Program
*/
#ifndef MENU_H
#include "bstree.h"
#include "InputValidator.h"
#include <string>
#include <vector>

/** @class Menu
    @brief extends BinarySearchTree to add user interface

    @internal Inheritance was used as a way to get the most mileage
    out of the private functions of BinarySearchTree. It would
    be possible to have written this another way. Upon
    inspection of the call graph, it is clear that only public
    members of BinarySearchTree are accessed, and a rewrite is probably
    merited.
*/
class Menu : public BinarySearchTree {
public:
  Menu();
  ~Menu();
private:
  /** iv is an inputvalidator shared by some
      user interaction routines.
  */
  InputValidator<int> iv;
  /** buf is an ugly solution to an ugly problem

      used as a target for getline to grab strings
      from the user. Since spaces are potentially valid
      filename components, istream<<s won't do.
   */
  char buf[5000];
  bool displayMenu();
  bool processResponse();
  void insertFile();
  void writeToFile();
  void insertInteger();
  void deleteInteger();
  void lookup();
  void displayTree();
  void generateDotFile();
};

#define MENU_H
#endif
