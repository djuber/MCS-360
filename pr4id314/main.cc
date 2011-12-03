/** @file main.cc
    @author Daniel Uber
    @brief Quick Check
*/

#include "menu.h"
/** @fn main
    start the menu system
*/
int main(){
  Menu M;
  return 0;
}

/**

   @mainpage Integer Dictionary Program
   @section intro_sec Introduction
   This is a simple BST as dictionary demonstration program.
   At each point, the user will have the option to
   add a number to the dictionary, look for a number in the
   dictionary (since no other information is associated with it,
   a found/not found response is displayed), remove a number
   from the dictionary, display the tree
   (via dot file or on the screen), save the numbers in the tree
   to a text file, display summary information about the tree, and
   quit the program. This program was written as programming
   assignment 4 for MCS 360, Fall 2011.

   @section install_sec Installation
   Typical installation is accomplished by using the make
   utility. `make run` will start the system after building.
   `make doc` will generate this documentation.
   `make clean` will restore the system to clean source.
   `make graphics` will process any saved dot files, generating
   svg and png images from them. These may be viewed with a web
   browser or an image utility such as emacs.
   An install target has not been provided.
   Simply move the compiled file to the
   target directory.

   @section overview_sec Overview
   The program can be understood as composed of the
   BinarySearchTree class, the Menu class which extends it,
   and a handful of utilities for managing the user interaction.
   The Menu class constructor essentially runs the program,
   and main only creates menu, which terminates when quit is selected.

   @section help_sec When Things Go Wrong
   Although some effort has been put into providing a reliable
   piece of software, occassionally the unforeseen and untested
   creeps in. Please contact duber3@uic.edu for assistance.
   Providing a log of the session where the bug occurred would
   be most helpful. Just copy the last few pages of screen output.

   @section bugs_sec Known Bugs
   I'm not entirely satisfied with the output of dot. A small
   effort was put into making the generated images properly
   reflect positioning (left items should be left, and right items
   should be right). This is an active question in the graphviz
   community, and the current best answer seems to be to
   generate custom svg where this is needed. The developers of
   dot have tried to make their placement as rational as possible,
   but this sometimes clobbers intent.

*/
